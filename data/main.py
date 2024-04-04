from cyaron import *


_n = ati([0,2,5,8,1e3,1e3+1145,5e3,8e3,1e4,5e4,8e4])
_q = ati([0,1,5,6,1e3+114,5e3+114,6e3+114,8e3+191,11451,19191,8e4+114])

num1 = ati([1e3])
num2 = ati([1e6])
num3 = ati([1e9])
for i in range(8,12):
    test_data = IO(file_prefix="T", data_id=i)
    n = _n[i]
    q = _q[i]
    if i<=3:
        num = num1[0]
    elif i>3 and i<=7:
        num = num2[0]
    else:
        num = num3[0]
    test_data.input_writeln(n,q)
    ls = Vector.random(n,[num],1)
    # ls = sum(ls, [])
    test_data.input_writeln(ls)
    for i in range(q):
        test_data.input_writeln(randint(1,3),randint(1, n//2),randint(n//2+1,n),randint(1,num))

    # test_data.output_gen("/Users/wangxinning/Documents/C++/data/T440228")

