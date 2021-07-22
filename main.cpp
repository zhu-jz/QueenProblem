// includes

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <cerrno>

// constants

enum
{
    A1=0, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8
};

const int FileA = 0x4;
const int FileB = 0x5;
const int FileC = 0x6;
const int FileD = 0x7;
const int FileE = 0x8;
const int FileF = 0x9;
const int FileG = 0xA;
const int FileH = 0xB;

const int Rank1 = 0x4;
const int Rank2 = 0x5;
const int Rank3 = 0x6;
const int Rank4 = 0x7;
const int Rank5 = 0x8;
const int Rank6 = 0x9;
const int Rank7 = 0xA;
const int Rank8 = 0xB;

const int SquareNum     = 64;
const int DeltaNb       = 2 * 119 + 1;
const int DeltaOffset   = 119;
const int QueenFlag     = 1;
const int MaxQueenNum   = 10;
const int MaxLen        = 80;

const int QueenInc[8] =
{
    -17, -16, -15, -1, +1, +15, +16, +17
};

const unsigned int Bits[MaxQueenNum+1] =
{
    0x0, 0x1, 0x3, 0x7, 0xF, 0x1F, 0x3F, 0x7F, 0xFF, 0x1FF, 0x3FF
};

const int Symmetry[8][SquareNum] =
{
    {
        A1,B1,C1,D1,E1,F1,G1,H1,
        A2,B2,C2,D2,E2,F2,G2,H2,
        A3,B3,C3,D3,E3,F3,G3,H3,
        A4,B4,C4,D4,E4,F4,G4,H4,
        A5,B5,C5,D5,E5,F5,G5,H5,
        A6,B6,C6,D6,E6,F6,G6,H6,
        A7,B7,C7,D7,E7,F7,G7,H7,
        A8,B8,C8,D8,E8,F8,G8,H8
    },

    {
        A1,A2,A3,A4,A5,A6,A7,A8,
        B1,B2,B3,B4,B5,B6,B7,B8,
        C1,C2,C3,C4,C5,C6,C7,C8,
        D1,D2,D3,D4,D5,D6,D7,D8,
        E1,E2,E3,E4,E5,E6,E7,E8,
        F1,F2,F3,F4,F5,F6,F7,F8,
        G1,G2,G3,G4,G5,G6,G7,G8,
        H1,H2,H3,H4,H5,H6,H7,H8
    },

    {
        H8,H7,H6,H5,H4,H3,H2,H1,
        G8,G7,G6,G5,G4,G3,G2,G1,
        F8,F7,F6,F5,F4,F3,F2,F1,
        E8,E7,E6,E5,E4,E3,E2,E1,
        D8,D7,D6,D5,D4,D3,D2,D1,
        C8,C7,C6,C5,C4,C3,C2,C1,
        B8,B7,B6,B5,B4,B3,B2,B1,
        A8,A7,A6,A5,A4,A3,A2,A1
    },

    {
        H8,G8,F8,E8,D8,C8,B8,A8,
        H7,G7,F7,E7,D7,C7,B7,A7,
        H6,G6,F6,E6,D6,C6,B6,A6,
        H5,G5,F5,E5,D5,C5,B5,A5,
        H4,G4,F4,E4,D4,C4,B4,A4,
        H3,G3,F3,E3,D3,C3,B3,A3,
        H2,G2,F2,E2,D2,C2,B2,A2,
        H1,G1,F1,E1,D1,C1,B1,A1
    },

    {
        H1,G1,F1,E1,D1,C1,B1,A1,
        H2,G2,F2,E2,D2,C2,B2,A2,
        H3,G3,F3,E3,D3,C3,B3,A3,
        H4,G4,F4,E4,D4,C4,B4,A4,
        H5,G5,F5,E5,D5,C5,B5,A5,
        H6,G6,F6,E6,D6,C6,B6,A6,
        H7,G7,F7,E7,D7,C7,B7,A7,
        H8,G8,F8,E8,D8,C8,B8,A8
    },

    {
        H1,H2,H3,H4,H5,H6,H7,H8,
        G1,G2,G3,G4,G5,G6,G7,G8,
        F1,F2,F3,F4,F5,F6,F7,F8,
        E1,E2,E3,E4,E5,E6,E7,E8,
        D1,D2,D3,D4,D5,D6,D7,D8,
        C1,C2,C3,C4,C5,C6,C7,C8,
        B1,B2,B3,B4,B5,B6,B7,B8,
        A1,A2,A3,A4,A5,A6,A7,A8
    },

    {
        A8,A7,A6,A5,A4,A3,A2,A1,
        B8,B7,B6,B5,B4,B3,B2,B1,
        C8,C7,C6,C5,C4,C3,C2,C1,
        D8,D7,D6,D5,D4,D3,D2,D1,
        E8,E7,E6,E5,E4,E3,E2,E1,
        F8,F7,F6,F5,F4,F3,F2,F1,
        G8,G7,G6,G5,G4,G3,G2,G1,
        H8,H7,H6,H5,H4,H3,H2,H1
    },

    {
        A8,B8,C8,D8,E8,F8,G8,H8,
        A7,B7,C7,D7,E7,F7,G7,H7,
        A6,B6,C6,D6,E6,F6,G6,H6,
        A5,B5,C5,D5,E5,F5,G5,H5,
        A4,B4,C4,D4,E4,F4,G4,H4,
        A3,B3,C3,D3,E3,F3,G3,H3,
        A2,B2,C2,D2,E2,F2,G2,H2,
        A1,B1,C1,D1,E1,F1,G1,H1
    }
};

// macros

#define DELTA_MASK(delta)      (DeltaMask[DeltaOffset+(delta)])

#undef ASSERT
#if DEBUG
#  define ASSERT(a) { if (!(a)) my_fatal("file \"%s\", line %d, assertion \"" #a "\" failed\n",__FILE__,__LINE__); }
#else
#  define ASSERT(a)
#endif

// types

typedef unsigned long long int uint64;
typedef unsigned int uint;

// variables

static int DeltaMask[DeltaNb];
static int SquareFrom64[SquareNum];
static int QueenPos[MaxQueenNum];
static int MSBTable[128+1]; //Most Significant Bit Table reflecting #rank and #file
static char FEN[MaxLen];

static int QueenNum, AtkSqNum;
static int unique, checked;
static FILE *Solution;

// prototypes

static bool     all_attacked    ();
static bool     symmetry        (const uint64 config);
static char     *gen_fen        (const uint64 config);
static int      set_value       (const char *str);
static uint64   next_per        (uint64 current);
static void     find_pos        (const uint64 config);
static void     init            ();
static void     is_valid        ();
static void     my_fatal        (const char format[], ...);
static void     solution_open   ();
static void     solution_close  ();
static void     solve           ();

// functions

static void init()
{
    int delta, inc;
    int dir, dist;
    int rank, file;
    int i;

    unique = 0;
    checked = 0;
    Solution = NULL;
    //LineSize = 0;

    solution_open();  // open a file to write solutions

    for (delta = 0; delta < DeltaNb; delta++)
    {
        DeltaMask[delta] = 0;
    }

    DeltaMask[DeltaOffset] |= QueenFlag; // square on which the queen is should be marked as attacked

    for (dir = 0; dir < 8; dir++)
    {
        inc = QueenInc[dir];

        for (dist = 1; dist < 8; dist++)
        {
            delta = inc * dist;
            DeltaMask[DeltaOffset+delta] |= QueenFlag;
        }
    }

    // init SquareFrom64[]
    i = 0;

    for (rank = Rank1; rank <= Rank8; rank++)
    {
        for (file = FileA; file <= FileH; file++)
        {
            SquareFrom64[i++] = (rank << 4) | file;
        }
    }

    // init QueenPos[]
    for (i = 0; i < MaxQueenNum; i++)
    {
        QueenPos[i] = 0;
    }

    // init MSBTable[]
    for (i = 0; i < 129; i++)
    {
        MSBTable[i] = (
            (i > 127) ? Rank8 :
            (i >  63) ? Rank7 :
            (i >  31) ? Rank6 :
            (i >  15) ? Rank5 :
            (i >   7) ? Rank4 :
            (i >   3) ? Rank3 :
            (i >   1) ? Rank2 : Rank1);
    }
}

static uint64 next_per(uint64 current)
{
    uint64 next; 				// next permutation of bits
    uint64 tmp;

    ASSERT(current != 0);

    tmp = (current | (current - 1)) + 1;
    next = tmp | ((((tmp & -tmp) / (current & -current)) >> 1) - 1);

    return next;
}

static char *gen_fen(const uint64 config)
{
    int pos, len;
    int file, rank;
    int sq, piece;
    int c;

    pos = 0;

    for (rank = 0; rank < 8; rank++)
    {
        for (file = 0; file < 8;)
        {
            sq = file + rank * 8;
            piece = (config >> sq) & 0x1;

            if (piece == 0)
            {
                for (len = 0; file < 8 && ((config >> sq++) & 0x1) == 0; file++, len++)
                    ;
                c = '0' + len;
            }
            else
            {
                c = 'Q';
                file++;
            }

            FEN[pos++] = c;
        }
        FEN[pos++] = '/';
    }

    FEN[pos-1] = ' '; // HACK: remove the last '/'
    sprintf(&FEN[pos],"w - - 0 1");

    return FEN;
}

static void find_pos(const uint64 config)
{
    int pos;
    int sq, bit;

    pos = 0;

    for (sq = 0; sq < SquareNum;)
    {
        bit = (config >> sq) & 0x1;

        if (bit == 0)
        {
            for (; sq < SquareNum && ((config >> sq) & 0x1) == 0; sq++)
                ;
        }
        else
        {
            ASSERT(pos < QueenNum);
            QueenPos[pos++] = SquareFrom64[sq];
            sq++;
        }
    }
}

static bool all_attacked()
{
    int sq, pos;
    int rank, file;
    int attacked, examined;
    char rank_mask, file_mask;

    char tmp;
    int i, j;

    attacked = 0;
    examined = 0;
    rank_mask = 0xFF;
    file_mask = 0xFF;

    for (pos = 0; pos < QueenNum; pos++)
    {
        rank = (QueenPos[pos] >> 4) - Rank1;
        file = (QueenPos[pos] & 0xF) - FileA;

        rank_mask &= ~(0x1 << rank);
        file_mask &= ~(0x1 << file);
    }

    i = rank_mask & -rank_mask;  // the least significant bit
    j = file_mask & -file_mask;

    for (rank = MSBTable[i]; rank_mask != 0;)
    {
        tmp = file_mask;

        for(file = MSBTable[j]; tmp != 0;)
        {
            sq = (rank << 4) | file;

            for (pos = 0; pos < QueenNum; pos++)
            {
                if(DELTA_MASK(sq - QueenPos[pos]))
                {
                    attacked++;
                    break;
                }
            }

            examined++;
            tmp &= tmp - 1; // tmp ^= (tmp & -tmp);
            file = MSBTable[tmp & -tmp];
        }

        rank_mask &= rank_mask - 1; // rank_mask ^= (rank_mask & -rank_mask);  //set the least significant bit to 0
        rank = MSBTable[rank_mask & -rank_mask];
    }

    if ((examined - attacked) == (SquareNum - AtkSqNum)) return true;

    return false;
}

static bool symmetry(const uint64 config)
{
    int sq, bit;
    int i, pos;

    int     sym[8][QueenNum];
    uint64  sym_cfg[8];

    pos = 0;

    for (i = 0; i < 8; i++)
    {
        sym_cfg[i] = (uint64)0x0;
    }

    // detect queen
    for (sq = 0; sq < SquareNum;)
    {
        bit = (config >> sq) & 0x1;

        if (bit == 0)
        {
            for (; sq < SquareNum && ((config >> sq) & 0x1) == 0; sq++)
                ;
        }
        else    //queen found
        {
            for (i = 0; i < 8; i++)  // 8 symmetries
            {
                ASSERT(pos < QueenNum);
                sym[i][pos] = Symmetry[i][sq];
            }
            pos++;
            sq++;
        }
    }

    for (i = 0; i < 8; i++)
    {
        for (pos = 0; pos < QueenNum; pos++)
        {
            sym_cfg[i] |= ((uint64)0x1 << sym[i][pos]);
        }

        if (config > sym_cfg[i]) return false; // all the config other than the minimum one are the ones which have been found already.
    }

    return true;
}

static void solve()
{
    uint64 config, max_cfg;

    config = Bits[QueenNum];
    ASSERT (config != 0);
    max_cfg = config << (64 - QueenNum);

    while (config <= max_cfg)
    {
        find_pos(config);
        checked++;

        if (all_attacked())
        {
            if (symmetry(config))
            {
                fprintf(Solution, "%s\n", gen_fen(config));
                unique++;
            }
        }

        config = next_per(config);  // last call would be next_per(max_cfg), resulting config is 0xffffffff
    }

    solution_close();
}

static int set_value(const char *str)
{
    int len, i;

    len = strlen(str);
    if (len < 1 || len > 2) my_fatal("invalid value: %s\n", str);

    for (i = 0; i < len; i++)
    {
        if (str[i] < '0' || str[i] > '9') my_fatal("invalid value: %s\n", str);
    }

    return atoi(str);
}

static void is_valid()
{
    char flag;

    flag = 0;

    if (QueenNum < 1 || QueenNum > 10) flag |= 0x1 << 0;
    if (AtkSqNum < 0 || AtkSqNum > 64) flag |= 0x1 << 1;

    if (flag)
    {
        printf("ERROR:\n");
        (flag < 3) ?
        (flag < 2) ? my_fatal("Queen number (1 to 10): %d\n", QueenNum)
                   : my_fatal("Attack number (0 to 64): %d\n", AtkSqNum)
                   : my_fatal("Queen number (1 to 10): %d\nAttack number (0 to 64): %d\n", QueenNum, AtkSqNum);
    }
}

static void my_fatal(const char format[], ...)
{
    va_list ap;

    ASSERT(format!=NULL);

    va_start(ap,format);
    vfprintf(stderr,format,ap);
    va_end(ap);

    exit(EXIT_FAILURE);
}

static void solution_open()
{
    char file_name[MaxLen];

    sprintf(file_name, "%d-%d.fen", QueenNum, AtkSqNum);
    Solution = fopen(file_name, "w");
    if (Solution == NULL) my_fatal("Couldn't open file \"%s\" for writing", file_name);
}

static void solution_close()
{
    if (Solution != NULL && fclose(Solution) == EOF)
    {
        my_fatal("solution_close(): fclose(): %s\n",strerror(errno));
    }
}

int main(int argc, char *argv[])
{
    const char *argument;
    int argnum;

    // set default value
    QueenNum = 5;
    AtkSqNum = 64;

    if (argc > 3) my_fatal("too many arguments\n");

    for (argnum = 1; argnum < argc;)
    {
        argument = argv[argnum];

        if (argument[0] == '-')
        {
            switch (argument[1])
            {
            case 'q':
            case 'Q':
                QueenNum = set_value(&argument[2]);
                argnum++;
                break;

            case 'n':
            case 'N':
                AtkSqNum = set_value(&argument[2]);
                argnum++;
                break;

            default:
                my_fatal("invalid arguments: %s\n", argument);

            }
        }
        else my_fatal("invalid arguments: %s\n", argument);
    }

    is_valid();
    init();
    solve();

    printf("\nQueen number = %d\nSquares attacked = %d\n", QueenNum, AtkSqNum);
    printf("\nThere are %d unique solutions, from all %d possible positions\n", unique, checked);

    return 1;
}
