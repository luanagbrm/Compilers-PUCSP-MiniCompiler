; ModuleID = 'minipc'
source_filename = "minipc"

@str = private unnamed_addr constant [5 x i8] c"true\00", align 1
@nl = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@str.1 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@nl.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define i32 @main(i32 %argc, ptr %argv) {
entry:
  %paramstr.result = alloca i32, align 4
  %prime = alloca i1, align 1
  %i = alloca i32, align 4
  %n = alloca i32, align 4
  %argv2 = alloca ptr, align 8
  %argc1 = alloca i32, align 4
  store i32 %argc, ptr %argc1, align 4
  store ptr %argv, ptr %argv2, align 8
  store i32 0, ptr %n, align 4
  store i32 0, ptr %i, align 4
  store i1 false, ptr %prime, align 1
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
  %lt = icmp slt i32 %n4, 2
  br i1 %lt, label %then, label %else

then:                                             ; preds = %paramstr.done
  store i1 false, ptr %prime, align 1
  br label %ifmerge

else:                                             ; preds = %paramstr.done
  store i1 true, ptr %prime, align 1
  store i32 2, ptr %i, align 4
  br label %while.cond

ifmerge:                                          ; preds = %while.end, %then
  %prime15 = load i1, ptr %prime, align 1
  br i1 %prime15, label %then16, label %else17

while.cond:                                       ; preds = %ifmerge12, %else
  %i5 = load i32, ptr %i, align 4
  %i6 = load i32, ptr %i, align 4
  %mul = mul i32 %i5, %i6
  %n7 = load i32, ptr %n, align 4
  %lte = icmp sle i32 %mul, %n7
  br i1 %lte, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %n8 = load i32, ptr %n, align 4
  %i9 = load i32, ptr %i, align 4
  %mod = srem i32 %n8, %i9
  %eq = icmp eq i32 %mod, 0
  br i1 %eq, label %then10, label %else11

while.end:                                        ; preds = %while.cond
  br label %ifmerge

then10:                                           ; preds = %while.body
  store i1 false, ptr %prime, align 1
  %n13 = load i32, ptr %n, align 4
  store i32 %n13, ptr %i, align 4
  br label %ifmerge12

else11:                                           ; preds = %while.body
  br label %ifmerge12

ifmerge12:                                        ; preds = %else11, %then10
  %i14 = load i32, ptr %i, align 4
  %add = add i32 %i14, 1
  store i32 %add, ptr %i, align 4
  br label %while.cond

then16:                                           ; preds = %ifmerge
  %0 = call i32 (ptr, ...) @printf(ptr @str)
  %1 = call i32 (ptr, ...) @printf(ptr @nl)
  br label %ifmerge18

else17:                                           ; preds = %ifmerge
  %2 = call i32 (ptr, ...) @printf(ptr @str.1)
  %3 = call i32 (ptr, ...) @printf(ptr @nl.2)
  br label %ifmerge18

ifmerge18:                                        ; preds = %else17, %then16
  ret i32 0
}

declare i32 @atoi(ptr)

declare i32 @printf(ptr, ...)
