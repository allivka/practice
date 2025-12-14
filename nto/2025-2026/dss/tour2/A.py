from decimal import Decimal, ROUND_HALF_UP
import math

r1, r2, r3, c, v0 = [Decimal(input()) for _ in range(5)]

R = (r1 * r2) / (r2 + r1) + r3

for i in range(1, 6):
    result = v0 * Decimal(str(math.exp(float(-Decimal(i) / R / c))))
    print(result.quantize(Decimal("0.01"), rounding=ROUND_HALF_UP), end=' ')
