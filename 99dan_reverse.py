print("# 9단 # # 8단 # # 7단 # # 6단 # # 5단 # # 4단 # # 3단 # # 2단 # ")
for i in range(9, 0, -1):
    for j in range(9, 1, -1):
        print(f"{j}X {i}={str(j * i).rjust(2)}", end=" ")
    print('')