```
Find The Easy Pass - Reverse Challenge
```

#Findings + Solution
>ran the executable
>asks for pass
>wrong pass puts out an error with 'Wrong Password'
>ran strings first to find anything good
>no luck
>opened it in ghidra
>searched with strings 'Wrong Password'
>in the assesmbly code found the function
>opened it in decompiler
>a lot of code cant undestand it
>opened it in immunity debugger
>set a breakpoint at the JUMP function above the password check
>ran the program in the debugger
>provided w a random password
>saw in the debugger my provied pass and another ASCII string
	fortran!
>used it as password
>worked!!!
>flag
	HTB{fortran!}