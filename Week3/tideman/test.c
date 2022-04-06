
existing pairs:
0:(d, a)
1:(b, c)
2:(c, a)
3:(a, b)
4:(d, b)
5:(d, c)


// 4 candidates, 5 voters => https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9#file-test4-txt
acbd bcda dcab dabc dbca



    // 4 candidates, 5 voters
    // ./tideman a3 b0 c1 d2
    // Votes
    /*
    a,b,c,d

    a,b,c,d

    a,c,d,b

    d,a,b,c

    d,a,c,b

    pairs: (a,b) (a,c) (a,d) (b,c) (c,d) (d,b)
    */
    // 4 candidates, 5 voters
    // ./tideman 3 0 1 2
    // Votes
    /*
    3, 0, 1, 2

    3, 0, 1, 2

    3, 1 2, 0

    2, 3, 0, 1

    2, 3, 1, 0

    pairs: (3,0) (3,1) (3,2) (0,1) (1,2) (2,0)
    */