/* look at the precondition/post condition/loop invariants in
   the auto_ghost_data.py file
   */

int simple__fail_missing_precondition(int a)
{
    a += 2;
    a = 4;
    a -= 5;
    return a;
}

int two_vars___fail(int a, int b)
{
    a = a + b;
    b = a - b;
    a = a - b;
    return a + b;
}

int if_join(int cond)
{
    int a = 10;
    if (cond)
    {
        a += 1;
    }
    else
    {
        a -= 4;
    }
    return a;
}

int if_join_different_length(int cond)
{
    int a = 10;
    if (cond)
    {
        a += 1;
    }
    else
    {
        a -= 4;
        a *= 2;
    }
    return a;
}

int if_join_multiple_variables(int cond)
{
    int a = 10;
    int b = 20;
    if (cond)
    {
        a += 1;
        b -= 1;
    }
    else
    {
        a -= 4;
        a -= b + 4;
        a *= 2;
    }
    return a * b;
}

int if_join_multiple_variables_no_ret(int cond)
{
    int a = 10;
    int b = 20;
    if (cond)
    {
        a += 1;
        b -= 1;
    }
    else
    {
        a -= 4;
        a -= b + 4;
        a *= 2;
    }
    return 0;
}

int elif_chain(int x, int y)
{
    int a = 1;
    if (x) { a = 2; }
    else if (y) { a = 2; a++; }
    else { a = 2; a++; a++; }
    return a;
}

int simple_for_loop___fail_missing_invariant(int n)
{
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        s += i;
    }
    return s;
}

struct point { int x; int y; };

struct point origin = {0};

struct point shift_diag___fail_overflow(struct point p, int offset)
{
    if (offset == 0)
    {
        return origin;
    }
    p.x += offset;
    p.y += offset;
    return p;
}

int fail_one_branch_undefined(int b)
{
    int a;
    if (b)
    {
        a = 2;
    }
    return a;
}

int one_branch_legal(int b)
{
    if (b)
    {
        int a = 2;
        (void) a;
    }
    return 0;
}

int fail_uninit(int b)
{
    int a;
    if (b)
    {
        a = 2;
    }
    return a + 1;
}

int init(int b)
{
    int a = 0;
    if (b)
    {
        a = 2;
    }
    return a + 1;
}

int fail_arr_undefined_behaviour(int i)
{
    int arr[8];
    arr[0] = 2;
    return arr[i];
}

int fail_zoltans_horrible_fail_arr_undefined_behaviour(int i)
{
    int arr[8];
    arr[0] = 2;
    arr[0] = 2 + arr[i];
    return arr[0];
    // technically, `return 4` is a valid compilation of this fn.
}

int fail_arr_undefined_behaviour2(int i, int j)
{
    int arr[8];
    if (j)
    {
        arr[0] = 2;
    }
    else
    {
        arr[1] = 3;
    }
    return arr[i];
}

// doesn't compile to graph lang
// int arr_loop_init(int j)
// {
//     int arr[8];
//     for (int i = 0; i < 8; i++)
//     {
//         arr[i] = 1;
//     }
//     return arr[j];
// }

int arr_static()
{
    int arr[8];
    arr[0] = 1;
    return arr[0];
}

// Correctly checking an functions with dead code all initialize their
// variables correctly adds a bit of complexity to the analysis, and, at
// least right now, it does not seem worth it (just get rid of the dead
// code)
//
// int unreachable_entry()
// {
//     for (int i = 0; i < 10; i++)
//     {
//         break;
//         return 1;
//     }
//     return 3;
// }

int straight_into_loop___fail_because_missing_invariant(int i)
{
    // need invariant to prove that i is initialized
    while (i < 10)
    {
        i++;
    }
    return i;
}

int overflow2___fail_overflow(int branch, int j)
{
    if (branch)
    {
        j += 1;
    }
    else
    {
        j += 2;
    }
    return j;
}

int greater_than_op___fail_overflow(int a, int b)
{
    return a > -b;
}

int branch_then_loop___fail_because_no_invariant(int cond, unsigned int a)
{
    a = a % 100;
    if (cond)
    {
        a += 1;
    }
    else
    {
        a *= 2;
        a += 1;
    }
    int i = 0;
    while (i < 100)
    {
        i += a;
    }
    return i * a;
}


int non_void_empty()
{
    return 0;
}

void empty()
{}

void almost_empty()
{
    return;
}

// void prototype();

struct rect
{
    struct point botleft;
    struct point topright;
};

struct rect grow(struct rect r)
{
    if (r.topright.x < 1024)
        r.topright.x += 1;
    if (r.topright.y < 1024)
        r.topright.y += 1;
    return r;
}
