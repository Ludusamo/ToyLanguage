int b = 0
int recurse()
	if (b != 5)
		b = b + 1
		recurse()
	return b
recurse()

bool a = true
bool b = a

int a = 5 * 2
int b = 10
if (a == b)
	print(5)
