# https://www.acmicpc.net/problem/16196

sn = input()
n = int(input())
region = set([input() for _ in range(n)])

days = [0, 31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30, 31]

def is_leap_year(year):
    return year % 400 == 0 or (year % 100 != 0 and year %4 == 0)

def get_valid_days(year, month):
    if month == 2 and is_leap_year(year):
        return 29
    return days[month]

def valid_region(code):
    return code in region

def valid_birth_code(code):
    year, month, day = map(int,[code[:4], code[4:6], code[6:]])
    if not 1900 <= year <= 2011:
        return False
    if not 1 <= month <= 12:
        return False
    if not 1 <= day <= get_valid_days(year, month):
        return False
    return True

def order_code(code):
    value = int(code)
    
    if value == 0:
        return 'I'
    
    if value % 2 == 1:
        return 'M'
    else:
        return 'F'

def valid_checksum(code):
    x = 0
    for a in code:
        x *= 2
        if a == 'X': x += 10
        else: x += int(a)
    return x%11 == 1

flag = valid_region(sn[:6])
flag &= valid_birth_code(sn[6:14])
flag &= valid_checksum(sn)

print(order_code(sn[14:17]) if flag else 'I')
