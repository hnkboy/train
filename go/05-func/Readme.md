包含的知识点 https://github.com/unknwon/the-way-to-go_ZH_CN/blob/master/eBook/04.2.md
1.包别名的使用
2.如果你导入了一个包却没有使用它，则会在构建程序时引发错误，如 imported and not used: os，这正是遵循了 Go 的格言：“没有不必要的代码！“。
3.函数里的代码（函数体）使用大括号 {} 括起来。左大括号 { 必须与方法的声明放在同一行，这是编译器的强制规定，否则你在使用 gofmt 时就会出现错误提示：
`build-error: syntax error: unexpected semicolon or newline before {`
（这是因为编译器会产生 func main() ; 这样的结果，很明显这错误的）
Go 语言虽然看起来不使用分号作为语句的结束，但实际上这一过程是由编译器自动完成，因此才会引发像上面这样的错误
4.只有当某个函数需要被外部包调用的时候才使用大写字母开头  fmt.Println（"hello, world"）
5.一个函数可以有多个返回值 func FunctionName (a typea, b typeb) (t1 type1, t2 type2),返回类型之间需要使用逗号分割
6. := 是声明并赋值，并且系统自动推断类型，不需要var关键字
