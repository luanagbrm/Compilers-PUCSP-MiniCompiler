{ factor.pas - Integer Factorization
  Usage: ./factor 84
  Output: 2 2 3 7
}
program Factor;

var
  n, d: integer;

begin
  n := paramstr(1);
  d := 2;
  while d * d <= n do
  begin
    while n mod d = 0 do
    begin
      write(d, ' ');
      n := n div d
    end;
    d := d + 1
  end;
  if n > 1 then
    write(n, ' ');
  writeln
end.
