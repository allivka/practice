import requests
url = "https://olimp.miet.ru/nto/2/send_task"
data = {"code": open("fib.nasm").read(), "id": 534146}
ans = requests.post(url,json=data)
print(ans.text)

# import requests
# url = "https://olimp.miet.ru/nto/2/send_task"
# data = {"code": """mov eax,6
#         mov ecx,0
#         mov ebx,1
#         mov edx,2
#         jmp loop
#         loop:
#         cmp edx,eax
#         je e
#         mov esi,ebx
#         add ebx,ecx
#         mov ecx,esi
#         inc edx
#         jmp loop
#         e:
#         """}
# ans = requests.post(url,json=data)
# print(ans.text)