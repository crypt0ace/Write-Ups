```
Impossible Password - Reverse
```

#Findings + Solution
>found this in strings
	SuperSeKretKey
>ran the binary
>provided the key
>seems like level 2
>opened it in radare2
>used 'aaaa' to analyzeall
>printed the main func
	pdf@main
>saw that it compare the string first at
	'0x0040090d'
>if ok then jumps to next one otherwise exits
>second string comp is at
	'0x00400961'
>saw a weird func being called at
	'0x0040094f'
>in radare2 look at the func
	s fcn.0040078d
>then print
>pdf
>found that it was just creating random characters as password
>back to main
	s main
	pdf
>now type this to open in read-write mode
	oo+
>now use 'V' to get in visual mode
>once in visual mode type 'p' to change the formats
>in the better visual mode, use 'c' to change values
>go to the jump func
	'0x00400968'
>use 'i' to insert hex characters
>add '9090' which denotes 'nops' which means the check wont be performed
>now exit r2 and run the binary
>after first check add anything in the next step and you'l get the flag
	HTB{40b949f92b86b18}