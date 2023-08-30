int join(int c)
{
    int a;
    if (c)
    {
        a = 1;
    }
    else
    {
        a = 2;
    }
    return a;
}

int signed_cast__fail_overflow(int c)
{
    if (c + 32 > 150)
        return 1;
    return 0;
}

int signed_cast(int c)
{
    int offset = 0x7fffffff;
    if (c > offset - 32)
        return -1;
    if (c + 32 > 150)
        return 1;
    return 0;
}

int unsigned_cast(unsigned int c)
{
    unsigned int offset = 65;
    if (c + 32 > offset)
        return 1;
    return 0;
}

int hang()
{
    while (1) {}
}

int used_undefined_variable1__fail()
{
    int a;
    return a + 0;
}

int used_undefined_variable2__fail(int cond)
{
    int a;
    if (cond)
        return a + 0;
    return 0;
}

int used_undefined_variable3__ok(int cond)
{
    int a;
    if (cond)
    {
        if (!cond)
        {
            return a + 1; // can't ever reach here, so we're all good
        }
    }
    return 0;
}


int used_undefined_array_element__fail_because_no_short_circuiting(int i)
{
    int a[10];
    a[0] = 3;
    a[1] = 1;
    a[2] = 4;
    if (0 <= i && i <= 2)
    {
        return a[i];
    }
    return 0;
}

int used_undefined_array_element__fail_if_i_eq_3(int i)
{
    int a[10];
    a[0] = 3;
    a[1] = 1;
    a[2] = 4;
    if (0 <= i && i <= 3)
    {
        return a[i];
    }
    return 0;
}

int used_undefined_array_element__fail_lots_indices(int i)
{
    int a[10];
    a[0] = 3;
    a[1] = 1;
    a[2] = 4;
    return a[i];
}


int branches(int i)
{
    int a;
    if (i)
    {
        a = 1;
    }
    if (!i)
    {
        a = 2;
    }
    return a + 1;
}

// (define-fun loop_invariant@5 ((a___int@v (_ BitVec 32)) (i___int@v (_ BitVec 32)) (loop@4@count (_ BitVec 64))) Bool (and (and (bvsle (_ bv0 32) i___int@v)
//                      (bvsle i___int@v (_ bv5 32)))
//                  (=> (bvsge i___int@v (_ bv3 32)) (= a___int@v (_ bv1 32)))
//             )
// )
int undefined_var_with_loops___fail_missing_invariant()
{
    // if i'm specifying a value for a potentially undefined variable
    // if it is indeed undefined, i won't be able to say anything about it (can't prove loop invariants)
    // otherwise, if the invariant holds, you're fine.
    int a;
    for (int i = 0; i < 10; i++)
        // loop invariant: i >= 3 ==> a = 1
        //                 0 <= i <= 5
    {
        if (i == 2)
        {
            a = 1;
        }
        if (i == 5)
        {
            return a + 1;
        }
    }
    return 0;
}

// (define-fun and6 ((a1 Bool) (a2 Bool) (a3 Bool) (a4 Bool) (a5 Bool) (a6 Bool)) Bool
//     (and a1 (and a2 (and a3 (and a4 (and a5 a6)))))
// )
// (define-fun even ((x (_ BitVec 32))) Bool (= (bvsmod x (_ bv2 32)) (_ bv0 32)))
// (define-fun odd ((x (_ BitVec 32))) Bool (distinct (bvsmod x (_ bv2 32)) (_ bv0 32)))
// (define-fun loop_invariant@9 ((a___int@v (_ BitVec 32)) (b___int@v (_ BitVec 32)) (c___int@v (_ BitVec 32)) (j___int@v (_ BitVec 32)) (loop@8@count (_ BitVec 64))) Bool
//     (and6 (bvsle (_ bv0 32) j___int@v)
//           (bvsle j___int@v (_ bv10 32))
//           (=> (and (bvsgt j___int@v (_ bv0 32)) (= c___int@v (_ bv1 32))) (= b___int@v (_ bv1 32)))
//           (=> (and (bvsgt j___int@v (_ bv0 32)) (= c___int@v (_ bv2 32))) (= a___int@v (_ bv2 32)))
//           (=> (and (bvsgt j___int@v (_ bv0 32)) (odd i___unsigned@v~1)) (= c___int@v (_ bv1 32)))
//           (=> (and (bvsgt j___int@v (_ bv0 32)) (even i___unsigned@v~1)) (= c___int@v (_ bv2 32)))
// ))
int zoltanstest___fails_because_missing_invariant(unsigned int i) {
    int a;
    int b;
    int c;

    for (int j = 0; j < 10; j++) {
        // loop invariant: 0 <= j <= 10
        //                 (j > 0 && c == 1) ==> b == 1
        //                 (j > 0 && c == 2) ==> a == 2
        //                 (j > 0 && i % 2 != 0) ==> c == 1
        //                 (j > 0 && i % 2 == 0) ==> c == 2
        if (i & 1) {
            b = 1;
            c = 1;
        }
        if (!(i & 1)) {
            a = 2;
            c = 2;
        }
    }
    if (c == 2) return a + 1;
    return b + 1;
}

int arith_sum(int n)
{
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        s += i;
    }
    return s;
}

int arith_sum_cond___fail_because_missing_invariants(unsigned int n, int fast)
{
    if (fast)
    {
        return n * (n + 1) / 2; // c parser doesn't allow signed division apparently
    }
    else
    {
        int s = 0;
        for (int i = 0; i < n; i++)
        {
            s += i;
        }
        return s;
    }
    return 0;
}

int loop_with_inner_var___fail_because_missing_invariant()
{
    int s = 0;
    for (int i = 0; i < 10; i++)
    {
        int a = i + 2;
        s += a;
    }
    return s;
}

int loop_with_inner_var_declared_outside___fail_because_missing_invariant()
    // a == 2
{
    int s = 0;
    int a;
    for (int i = 0; i < 10; i++)
        // 0 <= i <= 10
        // loop invariant: (i == 0) || (i > 0 && a_defined && (a == i + 2 - 1))
    {
        a = i + 2;
    }
    return a;
}

int loop_conditional___fails_because_no_precondition(int n)
{
    // should fail if n <= 0 (undefined var)
    int a;
    for (int i = 0; i < n; i++)
    {
        a = 1;
    }
    return a;
}

int loop_conditional___fails_because_incorrect(int n)
{
    int a;
    for (int i = 0; i < n; i++)
    // inv= i<=n
    {
        if (0)
            a = 1;
    }
    return a;
}

int loop_conditional_extra__fails_because_incorrect()
{
    int a;
    for (int i = 0; i < 10; i++)
    // inv= 0<=i<=10
    {
        if (i == 15)
        {
            a = 1; // never runs
        }
    }
    return a;
}

int loop_conditional_extra__fails_because_no_inv()
{
    int a;
    for (int i = 0; i < 10; i++)
    // inv= 0<=i<=10
    //      i >= 6 ==> a_defined
    {
        if (i == 5)
        {
            a = 1; // a_defined = true
        }
    }
    // adds proof_obligation: a_defined
    return a;
}


// (define-fun and5 ((a1 Bool) (a2 Bool) (a3 Bool) (a4 Bool) (a5 Bool)) Bool (and a1 (and a2 (and a3 (and a4 a5)))))
// (define-fun loop_invariant@5 ((a___int@v (_ BitVec 32)) (a___int@v@assigned Bool) (b___int@v (_ BitVec 32)) (b___int@v@assigned Bool) (i___int@v (_ BitVec 32)) (i___int@v@assigned Bool) (loop@4@count (_ BitVec 64)) (loop@4@count@assigned Bool)) Bool (and loop@4@count@assigned
//     (and5 i___int@v@assigned
//           (bvsle (_ bv0 32) i___int@v)
//           (bvsle i___int@v (_ bv10 32))
//           (=> (bvsle (_ bv3 32) i___int@v) (and a___int@v@assigned (= a___int@v (_ bv1 32))))
//           (=> (bvsle (_ bv6 32) i___int@v) b___int@v@assigned)
//     )
// ))
int loop_conditional_extra2__fails_because_no_inv()
{
    int a;
    int b;
    for (int i = 0; i < 10; i++)
    // inv= 0<=i<=10
    //      3 <= i ==> (a_defined && a = 1)
    //      6 <= i ==> b_defined
    //      i_assigned
    {
        if (i == 2)
        {
            a = 1;  // a_defined = true
        }
        if (i == 5)
        {
            b = a + 1; // b_defined = a_defined
        }
    }
    // adds proof_obligation: a_defined
    return b;
}

// strategy: if a variable is a loop target and it isn't defined on at least
// one loop header predecessor (we call it an unbounded target) then we need
// to insert varX_defined variables (ie. expressible in the loop invariant as
// defined(varX)).
//
// when emiting proof obligation about a variable v for a path p, and a node
// of p is a loop header where v is an unbounded target, we add to the path's
// conjunction defined(v).
//
//



int loop_conditional_extra2__fails_because_wrong_order()
{
    int a;
    int b;
    for (int i = 0; i < 10; i++)
    // inv= 0<=i<=10
    //      i >= 8 ==> a_defined
    //      i >= 6 ==> b_defined
    {
        if (i == 7)
        {
            a = 1;
        }
        if (i == 5)
        {
            // can't prove a_defined
            b = a + 1;
        }
    }
    // adds proof_obligation: a_defined
    return b;
}

int loop_conditional_extra3__fails_because_no_inv()
{
    int a;
    int b;
    int c;
    for (int i = 0; i < 10; i++)
    // inv= 0<=i<=10
    //      i >= 1 ==> a_defined
    //      i >= 6 ==> b_defined
    {
        if (i == 2)
        {
            a = 1;  // a_defined = true
        }
        if (i == 5)
        {
            b = a + 1; // b_defined = a_defined
            b = b + c; // b_defined = b_defined AND c_defined (ie. we need to apply dsa on x_defined variables)
        }
    }
    // adds proof_obligation: a_defined
    return b;
}

int multiple_loops___fail_missing_invariant()
{
    int i = 0;
    do
    {
        for (int j = 0; j < 10; j++)
        {
            i++;
        }
    } while (i < 100);
}


int ret_variable___fail_overflow(int ret)
{
    return ret + 1;
}

void dont_return_things(int ret)
{
    if (-100 < ret && ret < 100)
    {
        ret *= 2;
    }
}

int less_than(int n, int m)
{
    return n < m;
}

int multiple_ret_incarnations___fail_missing_invariants(int n)
{
    int i = 0;
    // having a function call in the condition forces the c parser to
    // re-arrange the graph around a little
    while (less_than(i, n))
    {
        i++;
        n--;
    }
    return i;
}

int callee(int a)
{
    return a + 1;
}

int caller(int b)
{
    return callee(b) * 2;
}

int caller2(int b)
{
    // (b+1) * ((b+1)*2)
    return callee(b) * caller(b);
}

int caller2___fails_wrong_post_condition(int b)
{
    // (b+1) * ((b+1)*2)
    return callee(b) * caller(b);
}

int f_many_args(int a, int b, int c)
{
    if (a > 0)
        a = b + 1;
    else
        a = c - 1;
    return a * 2;
}

int call_many_args(int flag)
{
    int v = f_many_args(flag, 1, 2);
    // if flag > 0 then v = 4 else v = 2
    int v1 = f_many_args(v-2, flag, flag);
    // flag > 0 --> v = 4 --> v-2>0
    // v-2>0 --> v>2 --> flag > 0
    // if v-2>0 then v1 = (flag + 1)*2 else v1 = (flag-1)*2
    // v-2>0 == flag >0
    // if flag > 0 then v1 = (flag + 1)*2 else v1 = (flag-1)*2
    return v1 + v;
    // if flag > 0 then v+v1 = 4+ (flag + 1)*2 else v+v1 = 2+(flag-1)*2
}

int call_many_args_once(int x, int y)
{
    return f_many_args(0, x, y); // returns (y-1)*2
}

int types()
{
    int a = 1;
    unsigned int b = 2;
    long c = 3;
    return a + b + c;
}


struct point { int x; int y; };

struct point mk_point()
{
    struct point p;
    p.x = 1;
    p.y = 2;
    return p;
}

struct point get_point()
{
    struct point p = mk_point();
    p.x = -1;
    return p;
}

void ghost_add_1__fail()
{
    return;
}

void ghost_add_3()
{
    ghost_add_1__fail();
    ghost_add_1__fail();
    ghost_add_1__fail();
    return;
}

void ghost_add_2__fail()
{
    ghost_add_1__fail();
    ghost_add_1__fail();
    ghost_add_1__fail();
    return;
}


void concrete_ghost_interaction(int n)
{
    for (int i = 0; i < n; i++)
    {
        ghost_add_1__fail();
    }
    return;
}

void concrete_ghost_interaction__fail(int n)
{
    for (int i = 0; i < n; i++)
    {
        ghost_add_1__fail();
    }
    return;
}

// all the intersting things are happening in the specification of those
// functions
void special_call__fail(int i, int a) {}
void loop_iteration_condition(int a)
{
    for (int i = 0; i < 10; i++)
    {
        special_call__fail(i, a);
    }
}
