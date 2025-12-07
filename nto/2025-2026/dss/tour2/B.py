from decimal import Decimal, ROUND_HALF_UP

M, m, r, w = [Decimal(input()) for _ in range(4)]

result = w * m * r * r / (2 * M)
print(result.quantize(Decimal("1.00"), rounding=ROUND_HALF_UP))
