int x = 0
x = x + 1


int recurse()
	if (x == 5)
		return x
	x = x + 1
	recurse()
recurse()

bool a = true
bool b = a

int a = 5 * 2
int b = 10
if (a == b)
	print(5)
