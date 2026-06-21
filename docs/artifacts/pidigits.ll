; ModuleID = 'minipc'
source_filename = "minipc"

@fmt = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@nl = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define i32 @arccot(i32 %0, i32 %1) {
entry:
  %neg = alloca i1, align 1
  %t = alloca i32, align 4
  %k = alloca i32, align 4
  %power = alloca i32, align 4
  %total = alloca i32, align 4
  %s = alloca i32, align 4
  %x = alloca i32, align 4
  %arccot.retval = alloca i32, align 4
  store i32 0, ptr %arccot.retval, align 4
  store i32 %0, ptr %x, align 4
  store i32 %1, ptr %s, align 4
  store i32 0, ptr %total, align 4
  store i32 0, ptr %power, align 4
  store i32 0, ptr %k, align 4
  store i32 0, ptr %t, align 4
  store i1 false, ptr %neg, align 1
  %s1 = load i32, ptr %s, align 4
  %x2 = load i32, ptr %x, align 4
  %div = sdiv i32 %s1, %x2
  store i32 %div, ptr %power, align 4
  %power3 = load i32, ptr %power, align 4
  store i32 %power3, ptr %total, align 4
  store i32 3, ptr %k, align 4
  store i1 true, ptr %neg, align 1
  %power4 = load i32, ptr %power, align 4
  %x5 = load i32, ptr %x, align 4
  %x6 = load i32, ptr %x, align 4
  %mul = mul i32 %x5, %x6
  %div7 = sdiv i32 %power4, %mul
  store i32 %div7, ptr %power, align 4
  br label %while.cond

exit:                                             ; preds = %while.end
  %retval = load i32, ptr %arccot.retval, align 4
  ret i32 %retval

while.cond:                                       ; preds = %ifmerge, %entry
  %power8 = load i32, ptr %power, align 4
  %k9 = load i32, ptr %k, align 4
  %div10 = sdiv i32 %power8, %k9
  %gt = icmp sgt i32 %div10, 0
  br i1 %gt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %power11 = load i32, ptr %power, align 4
  %k12 = load i32, ptr %k, align 4
  %div13 = sdiv i32 %power11, %k12
  store i32 %div13, ptr %t, align 4
  %neg14 = load i1, ptr %neg, align 1
  br i1 %neg14, label %then, label %else

while.end:                                        ; preds = %while.cond
  %total27 = load i32, ptr %total, align 4
  store i32 %total27, ptr %arccot.retval, align 4
  br label %exit

then:                                             ; preds = %while.body
  %total15 = load i32, ptr %total, align 4
  %t16 = load i32, ptr %t, align 4
  %sub = sub i32 %total15, %t16
  store i32 %sub, ptr %total, align 4
  br label %ifmerge

else:                                             ; preds = %while.body
  %total17 = load i32, ptr %total, align 4
  %t18 = load i32, ptr %t, align 4
  %add = add i32 %total17, %t18
  store i32 %add, ptr %total, align 4
  br label %ifmerge

ifmerge:                                          ; preds = %else, %then
  %neg19 = load i1, ptr %neg, align 1
  %not = xor i1 %neg19, true
  store i1 %not, ptr %neg, align 1
  %k20 = load i32, ptr %k, align 4
  %add21 = add i32 %k20, 2
  store i32 %add21, ptr %k, align 4
  %power22 = load i32, ptr %power, align 4
  %x23 = load i32, ptr %x, align 4
  %x24 = load i32, ptr %x, align 4
  %mul25 = mul i32 %x23, %x24
  %div26 = sdiv i32 %power22, %mul25
  store i32 %div26, ptr %power, align 4
  br label %while.cond
}

define i32 @main(i32 %argc, ptr %argv) {
entry:
  %paramstr.result = alloca i32, align 4
  %digit = alloca i32, align 4
  %d = alloca i32, align 4
  %result = alloca i32, align 4
  %pi4 = alloca i32, align 4
  %scale = alloca i32, align 4
  %i = alloca i32, align 4
  %n = alloca i32, align 4
  %argv2 = alloca ptr, align 8
  %argc1 = alloca i32, align 4
  store i32 %argc, ptr %argc1, align 4
  store ptr %argv, ptr %argv2, align 8
  store i32 0, ptr %n, align 4
  store i32 0, ptr %i, align 4
  store i32 0, ptr %scale, align 4
  store i32 0, ptr %pi4, align 4
  store i32 0, ptr %result, align 4
  store i32 0, ptr %d, align 4
  store i32 0, ptr %digit, align 4
  %argc.val = load i32, ptr %argc1, align 4
  store i32 0, ptr %paramstr.result, align 4
  %paramstr.oor = icmp sge i32 1, %argc.val
  br i1 %paramstr.oor, label %paramstr.done, label %paramstr.ok

paramstr.ok:                                      ; preds = %entry
  %argv3 = load ptr, ptr %argv2, align 8
  %argvelem = getelementptr ptr, ptr %argv3, i32 1
  %argstr = load ptr, ptr %argvelem, align 8
  %argval = call i32 @atoi(ptr %argstr)
  store i32 %argval, ptr %paramstr.result, align 4
  br label %paramstr.done

paramstr.done:                                    ; preds = %paramstr.ok, %entry
  %paramstr.val = load i32, ptr %paramstr.result, align 4
  store i32 %paramstr.val, ptr %n, align 4
  %n4 = load i32, ptr %n, align 4
  %gt = icmp sgt i32 %n4, 6
  br i1 %gt, label %then, label %else

then:                                             ; preds = %paramstr.done
  store i32 6, ptr %n, align 4
  br label %ifmerge

else:                                             ; preds = %paramstr.done
  br label %ifmerge

ifmerge:                                          ; preds = %else, %then
  %n5 = load i32, ptr %n, align 4
  %lt = icmp slt i32 %n5, 1
  br i1 %lt, label %then6, label %else7

then6:                                            ; preds = %ifmerge
  store i32 1, ptr %n, align 4
  br label %ifmerge8

else7:                                            ; preds = %ifmerge
  br label %ifmerge8

ifmerge8:                                         ; preds = %else7, %then6
  store i32 1, ptr %scale, align 4
  %n9 = load i32, ptr %n, align 4
  %add = add i32 %n9, 2
  store i32 1, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.body, %ifmerge8
  %i10 = load i32, ptr %i, align 4
  %for.cmp = icmp sle i32 %i10, %add
  br i1 %for.cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %scale11 = load i32, ptr %scale, align 4
  %mul = mul i32 %scale11, 10
  store i32 %mul, ptr %scale, align 4
  %cur = load i32, ptr %i, align 4
  %inc = add i32 %cur, 1
  store i32 %inc, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %scale12 = load i32, ptr %scale, align 4
  %call = call i32 @arccot(i32 5, i32 %scale12)
  %mul13 = mul i32 4, %call
  %scale14 = load i32, ptr %scale, align 4
  %call15 = call i32 @arccot(i32 239, i32 %scale14)
  %sub = sub i32 %mul13, %call15
  store i32 %sub, ptr %pi4, align 4
  %pi416 = load i32, ptr %pi4, align 4
  %mul17 = mul i32 %pi416, 4
  store i32 %mul17, ptr %result, align 4
  %result18 = load i32, ptr %result, align 4
  %div = sdiv i32 %result18, 1000
  store i32 %div, ptr %result, align 4
  store i32 1, ptr %d, align 4
  %n19 = load i32, ptr %n, align 4
  %sub20 = sub i32 %n19, 1
  store i32 1, ptr %i, align 4
  br label %for.cond21

for.cond21:                                       ; preds = %for.body22, %for.end
  %i24 = load i32, ptr %i, align 4
  %for.cmp25 = icmp sle i32 %i24, %sub20
  br i1 %for.cmp25, label %for.body22, label %for.end23

for.body22:                                       ; preds = %for.cond21
  %d26 = load i32, ptr %d, align 4
  %mul27 = mul i32 %d26, 10
  store i32 %mul27, ptr %d, align 4
  %cur28 = load i32, ptr %i, align 4
  %inc29 = add i32 %cur28, 1
  store i32 %inc29, ptr %i, align 4
  br label %for.cond21

for.end23:                                        ; preds = %for.cond21
  %n30 = load i32, ptr %n, align 4
  store i32 1, ptr %i, align 4
  br label %for.cond31

for.cond31:                                       ; preds = %for.body32, %for.end23
  %i34 = load i32, ptr %i, align 4
  %for.cmp35 = icmp sle i32 %i34, %n30
  br i1 %for.cmp35, label %for.body32, label %for.end33

for.body32:                                       ; preds = %for.cond31
  %result36 = load i32, ptr %result, align 4
  %d37 = load i32, ptr %d, align 4
  %div38 = sdiv i32 %result36, %d37
  store i32 %div38, ptr %digit, align 4
  %result39 = load i32, ptr %result, align 4
  %d40 = load i32, ptr %d, align 4
  %mod = srem i32 %result39, %d40
  store i32 %mod, ptr %result, align 4
  %digit41 = load i32, ptr %digit, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @fmt, i32 %digit41)
  %d42 = load i32, ptr %d, align 4
  %div43 = sdiv i32 %d42, 10
  store i32 %div43, ptr %d, align 4
  %cur44 = load i32, ptr %i, align 4
  %inc45 = add i32 %cur44, 1
  store i32 %inc45, ptr %i, align 4
  br label %for.cond31

for.end33:                                        ; preds = %for.cond31
  %1 = call i32 (ptr, ...) @printf(ptr @nl)
  ret i32 0
}

declare i32 @atoi(ptr)

declare i32 @printf(ptr, ...)
