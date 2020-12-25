class A(object):
    def foo(self, x):
        print("executing foo(%s,%s)" % (self, x))
        print('self:', self)
    @classmethod
    def class_foo(cls, x):
        print("executing class_foo(%s,%s)" % (cls, x))
        print('cls:', cls)
    @staticmethod
    def static_foo(x):
        print("executing static_foo(%s)" % x)
    def test(a,x):
        print("heelo", a, x)
a = A()
a.foo(1)
A.foo(2,3)
A.class_foo(2)
A.static_foo(3)
a.test(2)
A.test(1,2)
