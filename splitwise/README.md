# Requirements

There is concept of groups , groups have A,B,C users and multiple expenses, expenses has users-paid amount,
user can settle a expense, or settle group expense.

USERS |  A  |  B  |  C  |cumulative| + mean spend, -mean not paid
E1    |  5  |  6  | -11 |    0     |
E2    |  3  | -10 |  7  |    0     |
E3    |  5  |  3  |  19 |    27    |
total |  13 |  -1 |  15 |    27    |

suppose expense to be divided equally
27/3 = 9

C:15,A:13,B:-1
so settling expense is (high first clearing)
C paid 15 has to pay 9 (settled) so will recieve - 6
A paid 13 has to pay 9 (settled) so will recieve - 4
D paid -1 (borrowed one) has to pay 10 so give 4 to A and 6 to C
