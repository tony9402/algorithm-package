# https://www.acmicpc.net/problem/17471

n = int(input())
population = list(map(int, input().split()))
select = [False] * n
adj = []
min_diff = 0x3f3f3f3f

# flag가 True이면 인접한 1 선거구로 선택된 구역의 개수
# False이면 인접한 2 선거구 구역의 개수를 구합니다.
def travel(agent, flag):
    q = [agent]
    visit = [False]*n
    visit[q[0]] = True
    ret = 0
    while q:
        now = q.pop()
        ret += 1
        for next in adj[now]:
            if visit[next]: continue
            visit[next] = True
            if select[next] == flag:
                q.append(next)

    return ret

def choose_group_agent():
    g1_agent = -1
    g2_agent = -1

    for i in range(n):
        if select[i]:
            g1_agent = i
        else:
            g2_agent = i
    return (g1_agent, g2_agent)

def check(g1_agent, g2_agent):
    # 1 선거구로 선택된 구역의 개수
    # 2 선거구로 선택된 구역의 개수는 n - 1 선거구로 선택된 구역의 개수입니다.
    group1_num = select.count(True)
    # 선거구에 포함된 구역 이 없으면 False를 리턴합니다.
    if group1_num == 0 or group1_num == n: return False
    
    group1 = travel(g1_agent, True)
    if group1 != group1_num:
        return False
        
    group2 = travel(g2_agent, False)
    if group2 != n - group1_num:
        return False
    return True

# 인구 수의 차이를 구합니다.
def get_diff():
    population1 = 0
    population2 = 0
    for i in range(n):
        if select[i]: population1 += population[i] 
        else: population2 += population[i]

    return abs(population1 - population2)

def combination(i, n):
    global min_diff
    if i == n:
        g1_agent, g2_agent = choose_group_agent()
        if check(g1_agent, g2_agent):
            min_diff = min(min_diff, get_diff())
        return

    select[i] = True
    combination(i+1,n)
    select[i] = False
    combination(i+1,n)
    return

for i in range(n):
    adj.append(list(map(lambda x: int(x)-1,input().split()))[1:])

combination(0,n)
print(min_diff if min_diff != 0x3f3f3f3f else -1)
