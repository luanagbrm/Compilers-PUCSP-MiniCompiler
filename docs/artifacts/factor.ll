; ModuleID = 'minipc'
source_filename = "minipc"

@fmt = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@str = private unnamed_addr constant [2 x i8] c" \00", align 1
@fmt.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@str.2 = private unnamed_addr constant [2 x i8] c" \00", align 1
@nl = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define i32 @main(i32 %argc, ptr %argv) {
entry:
  %paramstr.result = alloca i32, align 4
  %d = alloca i32, align 4
  %n = alloca i32, align 4
  %argv2 = alloca ptr, align 8
  %argc1 = alloca i32, align 4
  store i32 %argc, ptr %argc1, align 4
  store ptr %argv, ptr %argv2, align 8
  store i32 0, ptr %n, align 4
  store i32 0, ptr %d, align 4
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
  store i32 2, ptr %d, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.end9, %paramstr.done
  %d4 = load i32, ptr %d, align 4
  %d5 = load i32, ptr %d, align 4
  %mul = mul i32 %d4, %d5
  %n6 = load i32, ptr %n, align 4
  %lte = icmp sle i32 %mul, %n6
  br i1 %lte, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  br label %while.cond7

while.end:                                        ; preds = %while.cond
  %n16 = load i32, ptr %n, align 4
  %gt = icmp sgt i32 %n16, 1
  br i1 %gt, label %then, label %else

while.cond7:                                      ; preds = %while.body8, %while.body
  %n10 = load i32, ptr %n, align 4
  %d11 = load i32, ptr %d, align 4
  %mod = srem i32 %n10, %d11
  %eq = icmp eq i32 %mod, 0
  br i1 %eq, label %while.body8, label %while.end9

while.body8:                                      ; preds = %while.cond7
  %d12 = load i32, ptr %d, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @fmt, i32 %d12)
  %1 = call i32 (ptr, ...) @printf(ptr @str)
  %n13 = load i32, ptr %n, align 4
  %d14 = load i32, ptr %d, align 4
  %div = sdiv i32 %n13, %d14
  store i32 %div, ptr %n, align 4
  br label %while.cond7

while.end9:                                       ; preds = %while.cond7
  %d15 = load i32, ptr %d, align 4
  %add = add i32 %d15, 1
  store i32 %add, ptr %d, align 4
  br label %while.cond

then:                                             ; preds = %while.end
  %n17 = load i32, ptr %n, align 4
  %2 = call i32 (ptr, ...) @printf(ptr @fmt.1, i32 %n17)
  %3 = call i32 (ptr, ...) @printf(ptr @str.2)
  br label %ifmerge

else:                                             ; preds = %while.end
  br label %ifmerge

ifmerge:                                          ; preds = %else, %then
  %4 = call i32 (ptr, ...) @printf(ptr @nl)
  ret i32 0
}

declare i32 @atoi(ptr)

declare i32 @printf(ptr, ...)
