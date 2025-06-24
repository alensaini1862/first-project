a= input('Enter Your Operater: ')
def add(x,y):
    sum = x+y
    return ("Your Result Is:" + str(sum))
def sub(x,y):
    sub = x-y
    return ("Your Result Is:" + str(sub))
def multiply(x,y):
    mul = x*y
    return ("Your Result Is:" + str(mul))
def Divieded(x,y):
    div = x/y
    return ("Your Result Is:" + str(div))
def moudles(x,y):
    mod = x%y
    return ("Your Result Is:" + str(mod))
if a=='+':
    print(add(int(input("Enter First Value: "))
       ,int(input("Enter Second Value: "))))
elif a=='-':
    print(sub(int(input("Enter First Value: "))
       ,int(input("Enter Second Value: "))))
elif a=='*':
    print(multiply(int(input("Enter First Value: "))
       ,int(input("Enter Second Value: "))))
elif a=='/':
    print(Divieded(int(input("Enter First Value: "))
       ,int(input("Enter Second Value: "))))
elif a=='%':
    print(moudles(int(input("Enter First Value: "))
       ,int(input("Enter Second Value: ")))
)
else:
    print("Operates Is Wrong")
    
