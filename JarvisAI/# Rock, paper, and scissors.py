my_list = [1, 2, 3, 4, 5]


count = 0

for element in my_list:
    
    count += 1
    print(element) # 1 3 5
    my_list.remove(element)

print(my_list) # 2 4 
print(count) # 3

