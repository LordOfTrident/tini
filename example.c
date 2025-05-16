#include <stdio.h> // printf

#define TINI_MULTILINE
#define TINI_INLINECOMMENTS
#define TINI_IMPLEMENTATION
#include "tini.h"

static const char *hook(char *sect, char *key, char *val, void *data) {
	(void)data;
	printf("  [%s] \"%s\" = \"%s\"\n", sect, key, val);
	return NULL;
}

static void error(int line, const char *err) {
	if (line > 0) printf("  Error at line #%i: %s\n", line, err);
	else          printf("  Error: %s\n", err);
}

int main(void) {
	int         errLine;
	const char *err;

#define EXAMPLE \
	"[my-section]\n" \
	"my-key=something # this is a comment\n" \
	"other-key=\"this is a string,\n" \
	"and it's multi-line!\""

	printf("==== Example #1 from string ====\n");
	err = tiniParseCstr(EXAMPLE, hook, &errLine, NULL);
	if (err != NULL) error(errLine, err);

#define EXAMPLE_ERR \
	"# Error below:\n" \
	"[sect\n" \
	"key = value\n"

	printf("\n==== Example #2 from string ====\n");
	err = tiniParseCstr(EXAMPLE_ERR, hook, &errLine, NULL);
	if (err != NULL) error(errLine, err);

	printf("\n==== Example #3 from file ====\n");
	err = tiniParsePath("example.ini", hook, &errLine, NULL);
	if (err != NULL) error(errLine, err);

	return 0;
}
