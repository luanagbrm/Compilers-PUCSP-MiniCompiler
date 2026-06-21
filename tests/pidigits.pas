{ pidigits.pas - Compute digits of Pi
  Uses Machin's formula: pi/4 = 4*arctan(1/5) - arctan(1/239)
  with scaled integer arithmetic
  Usage: ./pidigits 5
  Output: 31415
  Note: Limited to 7 digits due to 32-bit integer overflow
}
program PiDigits;

var
  n, i, scale, pi4, result, d, digit: integer;

{ Compute arctan(1/x) * scale using: s/x - s/(3*x^3) + s/(5*x^5) - ... }
function arccot(x, s: integer): integer;
var
  total, power, k, t: integer;
  neg: boolean;
begin
  power := s div x;
  total := power;
  k := 3;
  neg := true;
  power := power div (x * x);
  while power div k > 0 do
  begin
    t := power div k;
    if neg then
      total := total - t
    else
      total := total + t;
    neg := not neg;
    k := k + 2;
    power := power div (x * x)
  end;
  arccot := total
end;

begin
  n := paramstr(1);
  if n > 6 then
    n := 6;
  if n < 1 then
    n := 1;

  { Compute scale = 10^(n+2) for extra precision guard digits }
  scale := 1;
  for i := 1 to n + 2 do
    scale := scale * 10;

  { pi/4 = 4*arctan(1/5) - arctan(1/239) }
  pi4 := 4 * arccot(5, scale) - arccot(239, scale);
  result := pi4 * 4;

  { result = pi * 10^(n+2), has n+3 digits }
  { We want n digits, so divide by 10^3 (truncate, don't round) }
  result := result div 1000;

  { Now result has n digits. Print them. }
  d := 1;
  for i := 1 to n - 1 do
    d := d * 10;

  for i := 1 to n do
  begin
    digit := result div d;
    result := result mod d;
    write(digit);
    d := d div 10
  end;
  writeln
end.
