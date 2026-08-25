#!/usr/bin/env python3
"""Build one native release pack containing every problem in this repository."""

from __future__ import annotations

import argparse
from pathlib import Path

from alj_core import __version__
from alj_core.errors import JudgeError
from alj_core.pack_build import build_pack_for_problem_ids
from alj_core.paths import current_platform_id
from alj_core.problem_discovery import discover_problem_ids, validate_problem_sequence


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pack-id", default="basic")
    parser.add_argument("--output", type=Path, default=Path("dist/release"))
    parser.add_argument("--release-tag")
    parser.add_argument("--expected-platform")
    parser.add_argument(
        "--check-only",
        action="store_true",
        help="validate release inputs without compiling or writing a pack",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    root = Path(__file__).resolve().parents[1]
    platform_id = current_platform_id()
    problem_ids = discover_problem_ids(root)

    sequence_errors = validate_problem_sequence(problem_ids)
    if sequence_errors:
        raise JudgeError("invalid problem sequence:\n- " + "\n- ".join(sequence_errors))

    expected_tag = f"v{__version__}"
    if args.release_tag and args.release_tag != expected_tag:
        raise JudgeError(
            f"release tag {args.release_tag} does not match Judge version {expected_tag}"
        )
    if args.expected_platform and args.expected_platform != platform_id:
        raise JudgeError(f"runner platform is {platform_id}, expected {args.expected_platform}")

    output_dir = args.output if args.output.is_absolute() else root / args.output
    archive_name = f"{args.pack_id}-{__version__}-{platform_id}.aljpack"
    print(f"Problems: {len(problem_ids)} ({problem_ids[0]}..{problem_ids[-1]})")
    print(f"Platform: {platform_id}")
    print(f"Artifact: {output_dir / archive_name}")
    if args.check_only:
        return 0

    if not (root / "testlib.h").is_file() and not (root / "problems" / "testlib.h").is_file():
        raise JudgeError("testlib.h is required at the repository root or under problems/")

    result = build_pack_for_problem_ids(
        problem_ids,
        args.pack_id,
        platform_id,
        output_dir,
        root,
        # Release packs contain compiled problem tools, not reference submissions.
        # Correctness suites can run separately without repeating them per platform.
        solution_checks=[],
    )
    print(f"Built: {result.archive_path}")
    print(f"Checksum: {result.archive_path}.sha256")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except JudgeError as exc:
        raise SystemExit(f"error: {exc}") from exc
