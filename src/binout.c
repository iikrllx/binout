#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <getopt.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>

#define _LEN (CHAR_BIT * sizeof(uint64_t) - 1)
#define SHIFT_ONE(pos) (1UL << pos)
#define MOREN(a, b) ((a > b) ? a : b);
#define LESSN(a, b) ((a < b) ? a : b);

/* base bit operations */
#define SET_BIT(x, pos) (x | SHIFT_ONE(pos))
#define UNSET_BIT(x, pos) (x & ~(SHIFT_ONE(pos)))
#define SWITCH_BIT(x, pos) (x ^ (SHIFT_ONE(pos)))

static int position_opt = 0;
static int setbit_opt = 0;
static int unsetbit_opt = 0;
static int checkbit_opt = 0;
static int switchbit_opt = 0;
static int findflag_opt = 0;
static int pow_opt = 0;
static char *progname = "binout";

static void
usage(int status)
{
	if (status == EXIT_FAILURE) {
		fprintf(stderr, "Try '%s --help' for more information\n",
			progname);
	} else {
		printf("Usage: %s [options] ...\n", progname);
		fputs("\
Bits Operations\n\
\n\
    -p, --position=<0-63>               bit position between 0-63 range\n\
    -s, --set-bit=<dec>                 set the bit in the desired position\n\
    -u, --unset-bit=<dec>               unset the bit in the desired position\n\
    -w, --switch-bit=<dec>              switch the bit in the desired position\n\
    -c, --check-bit=<dec>               print the bits of the number\n\
    -f, --find-flag <dec> <dec>         find the flag between the two numbers\n\
    -o, --pow <base> <power>            power of the base number\n\
    -h, --help                          display this help and exit\n\
\n\
",stdout);
	}

	exit(status);
}

static int
notdigit(char *s)
{
	char *p = s;
	for (; *p; p++) {
		if (!(*p >= '0' && *p <= '9'))
			return 1;
	}

	return 0;
}

static int
bit_count(uint64_t x)
{
	unsigned int fl = 0;
	int btc = -1;

	for (int i = _LEN; i >= 0; i--) {
		unsigned int bit = (x & SHIFT_ONE(i)) != 0;

		if (bit == 1) {
			btc++;
			fl = 1;
		}

		if (bit != 1 && fl) btc++;
	}

	return btc;
}

static void
binary_print(uint64_t x)
{
	int fl = 0;

	for (int i = _LEN; i >= 0; i--) {
		unsigned int bit = (x & SHIFT_ONE(i)) != 0;

		if (bit == 1) {
			printf("\033[0;31m%d\033[0m", bit); /* red */
			fl = 1;
		}

		if (bit != 1 && fl)
			printf("\033[0;34m%d\033[0m", bit); /* blue */
	}
	printf("(\033[0;32m%ld\033[0m)\n", x);
}

static void
check_args(int argc, char **argv, int optind)
{
	for (int i = optind; i > (argc-3); i--) {
		if (!argv[i] || notdigit(argv[i]))
			usage(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	struct option long_options[] = {
		{ "set-bit",     required_argument,  NULL,  's' },
		{ "unset-bit",   required_argument,  NULL,  'u' },
		{ "check-bit",   required_argument,  NULL,  'c' },
		{ "switch-bit",  required_argument,  NULL,  'w' },
		{ "position",    required_argument,  NULL,  'p' },
		{ "find-flag",   required_argument,  NULL,  'f' },
		{ "pow",         required_argument,  NULL,  'o' },
		{ "help",        no_argument,        NULL,  'h' },
		{ NULL,          no_argument,        NULL,   0  }
	};

	unsigned int pos, base, power;
	uint64_t num = 0, res = 0, anum, bnum;

	for (;;) {
		int n = getopt_long(argc, argv, "s:u:c:w:p:f:o:h", long_options, NULL);

		if (n == -1)
			break;

		if (optarg && *optarg == '\0')
			usage(EXIT_FAILURE);

		switch (n) {
		case 'p':
			position_opt = 1;
			pos = atoi(optarg);
			if (pos > 63) usage(EXIT_FAILURE);
			break;

		case 's':
			setbit_opt = 1;
			num = atol(optarg);
			break;

		case 'u':
			unsetbit_opt = 1;
			num = atol(optarg);
			break;

		case 'c':
			checkbit_opt = 1;
			/* strtoul(const char *start, char **end, int radix)
			   If the value of 'radix' is zero, the syntax expected is
			   similar to that of integer constants 0X, 0x, 0 (hex, octal, dec) */
			num = strtoul(optarg, NULL, 0);
			break;

		case 'w':
			switchbit_opt = 1;
			num = atol(optarg);
			break;

		case 'f':
			findflag_opt = 1;
			check_args(argc, argv, optind);
			bnum = atol(argv[optind]);
			anum = atol(argv[optind-1]);
			break;

		case 'o':
			pow_opt = 1;
			check_args(argc, argv, optind);
			power = atoi(argv[optind]);
			base = atoi(argv[optind-1]);
			break;

		case 'h':
			usage(EXIT_SUCCESS);
			break;

		case '?':
			usage(EXIT_FAILURE);
			break;
		}
	}

	if (position_opt & setbit_opt)
		res = SET_BIT(num, pos);

	if (position_opt & unsetbit_opt)
		res = UNSET_BIT(num, pos);

	if (position_opt & switchbit_opt)
		res = SWITCH_BIT(num, pos);

	if (checkbit_opt)
		binary_print(num);

	if (findflag_opt) {
		if (anum & bnum) {
			uint64_t less, more;
			unsigned int nspace;

			printf("Flag found:\n");

			less = LESSN(anum, bnum);
			more = MOREN(anum, bnum);
			nspace = (bit_count(more) - bit_count(less));

			printf("%*s", nspace, "");
			binary_print(less);
			binary_print(more);
		} else
			printf("Flag not found\n");
	}

	if (pow_opt)
		printf("%0.f\n", pow((double)base, (double)power));

	if (!checkbit_opt && !findflag_opt && !pow_opt)
		binary_print(res);

	return 0;
}
