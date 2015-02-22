#include <stdio.h>

#define IN 1
#define OUT 0

int main(int argc, char *argv[]) {

	if (argc != 2)
	{
		printf("usage: %s filename\n", argv[0]);
		return 0;
	}

	char *fn = argv[1];
	FILE *fp = fopen(fn, "r");

	int nl, nw, nc, c, state;

	nl = nw = nc = 0;
	state = OUT;
	while((c = fgetc(fp)) != EOF) {
		nc++;
		if (c == '\n')
			nl++;

		if (c == ' ' || c == '\t' || c == '\n') {
			state = OUT;
		} else if (state == OUT) {
			state = IN;
			nw++;
		}
	}
	printf("%d\t%d\t%d\n", nl, nw, nc);

}
