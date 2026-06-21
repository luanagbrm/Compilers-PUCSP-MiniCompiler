{ fibonacci.pas - Fibonacci Number
  Usage: ./fibonacci 10
  Output: 55
}
program Fibonacci;

var
  n, i, a, b, temp: integer;

begin
  n := paramstr(1);
  if n <= 0 then
    writeln(0)
  else if n = 1 then
    writeln(1)
  else
  begin
    a := 0;
    b := 1;
    for i := 2 to n do
    begin
      temp := a + b;
      a := b;
      b := temp
    end;
    writeln(b)
  end
end.
