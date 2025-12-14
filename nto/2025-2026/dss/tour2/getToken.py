import requests
url = "https://olimp.miet.ru/nto/2/get_token"
data = {"id": 534146}
res = requests.post(url,json=data)
print(res.text)