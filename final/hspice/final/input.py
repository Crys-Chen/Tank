
# for i in range(1,16):
#     print("X",i," A",i," B",i," Co",i-1," Co",i," Y",i," adder",sep='')

def func(a,b,ci,n):
    A = [a&1]
    B = [b&1]
    
    a1 = a
    b1 = b
    while a1>>1:
        A.append((a1>>1) & 1)
        a1 = a1 >> 1
        
    while b1>>1:
        B.append((b1>>1) & 1)
        b1 = b1 >> 1
    
    S = a + b + ci
    # print("lenA=",len(A),"shift=",bin(shift))
    Co = (S >> n) & 1
    shift = (2 << (n-1)) - 1
    S = S & shift
    print("* A =",a," B =",b," Ci =",ci)
    print("* S =",S,"=",bin(S)," Co =",Co)
    
    for i in range(0,len(A)):
        if(A[i]):
            print("VA", i, "  A", i, "  GND","  PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V)",sep='')
        else:
            print("VA", i, "  A", i, "  GND","  PWL(0ns 0V `start-delta` 0V start 00 `end-delta` 00 end 0V)",sep='')
    
    for i in range(0,len(B)):
        if(B[i]):
            print("VB", i, "  B", i, "  GND","  PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V)",sep='')
        else:
            print("VB", i, "  B", i, "  GND","  PWL(0ns 0V `start-delta` 0V start 00 `end-delta` 00 end 0V)",sep='')
        
    if(ci):
        print("VC0  C0  GND  PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V)",sep='')
    else:
        print("VC0  C0  GND  PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V)",sep='')


    


# a = 0b11100101
# b = 0b00011010
# Ci=1
# a = 0b11111111
# b = 0b11111111
# ci = 0
# func(a,b,ci)

# a = 100
# b = 100
# ci = 1
# func(a,b,ci)

# a=32768
# b=32768
# ci=1
# func(a,b,ci,16)

# a = 0b1010011011100001
# b = 0b0101100100011110
# ci=1
# func(a,b,ci,16)
        
# a = 65535
# b = 65535
# ci=0
# func(a,b,ci,16)

