; ModuleID = 'minipc'
source_filename = "minipc"

@fmt = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@nl = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@fmt.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@nl.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@fmt.3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@nl.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define i32 @main(i32 %argc, ptr %argv) {
entry:
  %paramstr.result = alloca i32, align 4
  %temp = alloca i32, align 4
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  %i = alloca i32, align 4
  %n = alloca i32, align 4
  %argv2 = alloca ptr, align 8
  %argc1 = alloca i32, align 4
  store i32 %argc, ptr %argc1, align 4
  store ptr %argv, ptr %argv2, align 8
  store i32 0, ptr %n, align 4
  store i32 0, ptr %i, align 4
  store i32 0, ptr %a, align 4
  store i32 0, ptr %b, align 4
  store i32 0, ptr %temp, align 4
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
  %lte = icmp sle i32 %n4, 0
  br i1 %lte, label %then, label %else

then:                                             ; preds = %paramstr.done
  %0 = call i32 (ptr, ...) @printf(ptr @fmt, i32 0)
  %1 = call i32 (ptr, ...) @printf(ptr @nl)
  br label %ifmerge

else:                                             ; preds = %paramstr.done
  %n5 = load i32, ptr %n, align 4
  %eq = icmp eq i32 %n5, 1
  br i1 %eq, label %then6, label %else7

ifmerge:                                          ; preds = %ifmerge8, %then
  ret i32 0

then6:                                            ; preds = %else
  %2 = call i32 (ptr, ...) @printf(ptr @fmt.1, i32 1)
  %3 = call i32 (ptr, ...) @printf(ptr @nl.2)
  br label %ifmerge8

else7:                                            ; preds = %else
  store i32 0, ptr %a, align 4
  store i32 1, ptr %b, align 4
  %n9 = load i32, ptr %n, align 4
  store i32 2, ptr %i, align 4
  br label %for.cond

ifmerge8:                                         ; preds = %for.end, %then6
  br label %ifmerge

for.cond:                                         ; preds = %for.body, %else7
  %i10 = load i32, ptr %i, align 4
  %for.cmp = icmp sle i32 %i10, %n9
  br i1 %for.cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %a11 = load i32, ptr %a, align 4
  %b12 = load i32, ptr %b, align 4
  %add = add i32 %a11, %b12
  store i32 %add, ptr %temp, align 4
  %b13 = load i32, ptr %b, align 4
  store i32 %b13, ptr %a, align 4
  %temp14 = load i32, ptr %temp, align 4
  store i32 %temp14, ptr %b, align 4
  %cur = load i32, ptr %i, align 4
  %inc = add i32 %cur, 1
  store i32 %inc, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %b15 = load i32, ptr %b, align 4
  %4 = call i32 (ptr, ...) @printf(ptr @fmt.3, i32 %b15)
  %5 = call i32 (ptr, ...) @printf(ptr @nl.4)
  br label %ifmerge8
}

declare i32 @atoi(ptr)

declare i32 @printf(ptr, ...)
