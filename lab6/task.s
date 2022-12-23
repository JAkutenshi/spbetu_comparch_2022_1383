.global function
#rdi - int *res_arr, rsi - int *nums_arr, rdx - int k_inter, rcx - int count_N, r8 - int *left_arrarr, r9 - int *max_res
function:
	lodsd
	push rcx
	mov rcx, rdx
f_interval:
	cmp eax, [r8+rcx*4-4]# сравниваем с крайней правой границой
	jge end_find
	loop f_interval
	jmp exit
end_find:
	inc dword ptr [rdi+rcx*4-4]
  cmp eax, [r9+rcx*4-4]
  jl exit
  mov dword ptr [r9+rcx*4-4], eax
exit:
	pop rcx
	loop function
	ret
