
; HELLO1.ASM -  »i»e»f»d»o»Z»c»c»U»u »W»Z»f»g»^»u »i»m»Z»V»c»d»_ »e»f»d»X»f»U»b»b»q »a»U»V.»f»U»V. N1
;               »e»d »Y»^»g»l»^»e»a»^»c»Z "«Û»f»k»^»h»Z»`»h»i»f»U »`»d»b»e»r»t»h»Z»f»U"
; *****************************************************************
; »B»U»]»c»U»m»Z»c»^»Z: »D»f»d»X»f»U»b»b»U »j»d»f»b»^»f»i»Z»h »^ »W»q»W»d»Y»^»h »c»U »s»`»f»U»c »e»f»^»W»Z»h»g»h»W»^»Z
;             »e»d»a»r»]»d»W»U»h»Z»a»u »g »e»d»b»d»o»r»t »j»i»c»`»l»^»^ «˜»C»F "«ı»q»W»d»Y »g»h»f»d»`»^"
;             (»c»d»b»Z»f 09 »e»f»Z»f»q»W»U»c»^»Z 21h), »`»d»h»d»f»U»u:
;              - »d»V»Z»g»e»Z»m»^»W»U»Z»h »W»q»W»d»Y »c»U »s»`»f»U»c »g»h»f»d»`»^ »g»^»b»W»d»a»d»W,
;                »]»U»`»U»c»m»^»W»U»t»o»Z»_»g»u »]»c»U»`»d»b "$";
;              - »h»f»Z»V»i»Z»h »]»U»Y»U»c»^»u »W »f»Z»X»^»g»h»f»Z ah »c»d»b»Z»f»U »j»i»c»`»l»^»^=09h,
;                »U »W »f»Z»X»^»g»h»f»Z dx -  »g»b»Z»o»Z»c»^»u  »U»Y»f»Z»g»U  »W»q»W»d»Y»^»b»d»_
;                »g»h»f»d»`»^;
;              - »^»g»e»d»a»r»]»i»Z»h »f»Z»X»^»g»h»f  ax  »^  »c»Z »g»d»k»f»U»c»u»Z»h »Z»X»d
;                »g»d»Y»Z»f»\»^»b»d»Z.
; ******************************************************************

   DOSSEG                                      ; «˚»U»Y»U»c»^»Z »g»Z»X»b»Z»c»h»d»W »e»d»Y «˜»C»F
   .MODEL  SMALL                               ; »A»d»Y»Z»a»r »e»U»b»u»h»^-SMALL(»A»U»a»U»u)
   .STACK  100h                                ; »C»h»W»Z»g»h»^ »e»d»Y »F»h»Z»` 256 »V»U»_»h
   .DATA                                       ; »B»U»m»U»a»d »g»Z»X»b»Z»c»h»U »Y»U»c»c»q»k
Greeting  LABEL  BYTE                          ; »G»Z»`»g»h  »e»f»^»W»Z»h»g»h»W»^»u
   DB '«ı»U»g »e»f»^»W»Z»h»g»h»W»i»Z»h »g»h.»X»f.1383 - »I»Z»Y»d»f»d»W»U »C»`»g»U»c»U',13,10,'$'
   .CODE                                ; »B»U»m»U»a»d »g»Z»X»b»Z»c»h»U »`»d»Y»U
   mov  ax, @data                        ; «˚»U»X»f»i»]»`»U »W DS »U»Y»f»Z»g»U »c»U»m»U»a»U
   mov  ds, ax                           ; »g»Z»X»b»Z»c»h»U »Y»U»c»c»q»k
   mov  dx, OFFSET Greeting              ; «˚»U»X»f»i»]»`»U »W dx »g»b»Z»o»Z»c»^»u
                                        ; »U»Y»f»Z»g»U »h»Z»`»g»h»U »e»f»^»W»Z»h»g»h»W»^»u
DisplayGreeting:
   mov  ah, 9                            ; # »j»i»c»`»l»^»^ «˜»C»F »e»Z»m»U»h»^ »g»h»f»d»`»^
   int  21h                             ; »W»q»W»d»Y »c»U »s»`»f»U»c  »e»f»^»W»Z»h»g»h»W»^»u
   mov  ah, 4ch                          ; # »j»i»c»`»l»^»^ «˜»C»F »]»U»W»Z»f»n»Z»c»^»u »e»f»d»X»f»U»b»b»q
   int  21h                             ; »]»U»W»Z»f»n»Z»c»^»Z »e»f»d»X»f»U»b»b»q »^ »W»q»k»d»Y »W «˜»C»F
   END
