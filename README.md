# CASM-----汇编器
## 0.1a
+ 基础版本，实现了：
	- 1. mov
	- 2. cmp
	- 3. jmp
	- 4. add
	- 5. ret
	- 6. retf
	- 7. int
	- 8. push
	- 9. pop
	- 10. pusha
	- 11. popa
## 语法
- CASM的语法非常不同，他既有点AT&T语法的影子,也有点intel汇编的样子
接下来是一段CASM汇编代码
```c
mov $02,ecx
mov %ecx,eax
mov $68,edx
int 36
```