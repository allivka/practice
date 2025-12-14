Va, Vb, Vc, C, R, t = [float(input()) for _ in range(6)]

part = ((Vc - Vb) / (Va - Vb)) if Va != Vb else 0

lost = Vc / R * t / 3.6

result = max(C * part - lost, 0)


print(int(result))
