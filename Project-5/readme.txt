One issue with this program is I wasn't able to figure out/
I ran out of time to error check for preventing an account
from being overdrawn. Which ultimately means, I wasn't
able to implement the drawing money from another Bond or
Money Market account.

Deposit, move and history should work fine. Move is iffy
because I call withraw in it, and I didn't do the error
checking for withdraw transactions.

Other than the overdraw (now people can have infinite money),
the transactions appear to be working properly.

There is also memory leaks, and I didn't have a lot of time to
fix them.



