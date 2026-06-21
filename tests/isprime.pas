{ isprime.pas - Prime Number Check
  Usage: ./isprime 17
  Output: true
}
program IsPrime;

var
  n, i: integer;
  prime: boolean;

begin
  n := paramstr(1);
  if n < 2 then
    prime := false
  else
  begin
    prime := true;
    i := 2;
    while i * i <= n do
    begin
      if n mod i = 0 then
      begin
        prime := false;
        i := n  { break out of loop }
      end;
      i := i + 1
    end
  end;
  if prime then
    writeln('true')
  else
    writeln('false')
end.
