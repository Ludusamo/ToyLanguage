bool b = true
bool recurse()
	if (b)
		b = false
		recurse()
	return b
bool c = recurse()

bool a = true
bool b = a

int a = 5 * 2
int b = 10
if (a == b)
	print(5)
