from decimal import Decimal, ROUND_HALF_UP
import math

r1, r2, r3, c, c0 = [Decimal(input()) for _ in range(5)]

R = (r1 * r2) / (r2 + r1) + r3

for i in range(0, 6):
    result = Decimal(1) - Decimal(str(math.exp(Decimal(float(-i / R / c)))))
    print(result.quantize(Decimal("1.00"), rounding=ROUND_HALF_UP))
