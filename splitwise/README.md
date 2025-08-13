# Requirements

There is concept of groups, groups have A,B,C users and multiple expenses, expenses has users-paid-owed amount.
user can settle a expense, or settle group expense.

| Expenses     |  A  |  B  |  C  | Bill Amount |
| ---------    | --- | --- | --- | ----------- |
| E1 - paid    |  5  |  6  |  0  |     11      |
| E1 - owed    |  2  |  5  |  4  |     11      |
| E1 - balance |  3  |  1  |  -4 |     11      |
| E2 - paid    |  3  |  0  |  7  |     10      |
| E2 - owed    |  3  |  3  |  4  |     10      |
| E2 - balance |  0  |  -3 |  3  |     10      |
| E3 - paid    |  5  |  3  |  19 |     27      |
| E3 - owed    |  9  |  9  |  9  |     27      |
| E3 - balance |  -4 |  -6 |  10 |     27      |
| total balance|  -1 |  -8 |  9  |             |

settling E1
c owes 1 to B
c owes 3 to A

settling all Expenses
A owes 1 to C
B owes 8 to C

## Algorithm

here finaly balance of all user sum should be equal to zero
for huge user base example

| users | A | B | C | D | E | F |
| --- | --- | --- | --- | --- | --- | --- |
| balance | 90 | -70 | -40 | 80 | -100 | 40 |

we have to develop graph of settle expense between user such that minimal edges are made
E owes -> A : 90
B owes -> D : 70
C owes -> F : 40
E owes -> D : 10

will make most +ve and most -ve number to settle first will do this using heap.
