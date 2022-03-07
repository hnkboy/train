class Test:
    a = 1
    def __init__(self):
        self.b = 2
        print("hello")
    def cal(self):
        print("self")
    def call():
        print("6")
t = Test()
print(Test.a, t.b)
t.cal()
Test.cal(1)
Test.call()

