//Complex.java
//Represents complex numbers as a pair of doubles
//PA6
//Ian Feekes
//#1474914
//CMPS11

class Complex
{
 private double re;
 private double im;

 public static final Complex ONE=Complex.valueOf(1,0);
 public static final Complex ZERO=Complex.valueOf(0,0);
 public static final Complex I=Complex.valueOf(0,1);

 Complex(double a, double b)
 {
  this.re=a;
  this.im=b;
 }

 Complex(double a)
 {
  this.re=a;
  this.im=0;
 }

 Complex(String s)//utilizes parseComplex() code
 {
  double[] C=parseComplex(s);
  this.re=C[0];
  this.im=C[1];
 }

 Complex copy()//creates and returns an identical copy of this complex
 {
  Complex newOne = new Complex(this.Re(), this.Im());
  return newOne;
 }

 Complex add(Complex z)//adds the real coefficients and adds the imaginary coefficients
 {
  Complex added = new Complex(this.Re(), this.Im());
  added.re+=z.Re();
  added.im+=z.Im();
  return added;
 }

 Complex negate()
 {
  Complex opposite = new Complex(this.Re(), this.Im());
  opposite.im*=-1;//multiplying the real and imaginary coefficients by -1 gives for the opposite values desired
  opposite.re*=-1;
  return opposite;
 }

 Complex sub(Complex z)//subtracts the real coefficients and finds the difference of the imaginary coefficients separately
 {
  Complex subtracted = new Complex(this.Re(), this.Im());
  subtracted.re-=z.Re();
  subtracted.im-=z.Im();
  return subtracted;
 }

 Complex mult(Complex z)
 {
  Complex multiplied = new Complex(this.Re(), this.Im());
  multiplied.re=this.Re()*z.Re()-(this.Im()*z.Im());
  multiplied.im=(this.Re()*z.Im())+(this.Im()*z.Re());
  return multiplied;
 }

 Complex recip()
 {
  if(this.equals(Complex.ZERO))
  throw new ArithmeticException("illegal value");//error message and exception
  Complex reciprocal = new Complex(this.Re(),(this.Im()*-1));
  reciprocal.re/=((this.Re()*this.Re())+(this.Im()*this.Im()));
  reciprocal.im/=((this.Re()*this.Re())+(this.Im()*this.Im()));
  return reciprocal;
 }

 Complex div(Complex z)
 {
  if(z.equals(Complex.ZERO)) throw new ArithmeticException("illegal value");//error message and exception
  Complex divided= new Complex(this.Re(), this.Im());
  divided.re=((this.Re()*z.Re())+(this.Im()*z.Im()))/((z.Re()*z.Re())+(z.Im()*z.Im()));
  divided.im=((this.Re()*z.Im())+(this.Im()*z.Re()))/((z.Re()*z.Re())+(z.Im()*z.Im()));
  return divided;
 }

 Complex conj()
 {
  Complex conjugate = new Complex(this.Re(), this.Im());
  conjugate.im*=-1;
  return conjugate;
 }

 double Re()//to be called in math methods so we don't accidentely manipulate the variables of our preexisting complex numbers
 {
  return re;
 }

 double Im()//to be called in math methods so we don't accidentely manipulate the variables of our preexisting complex numbers
 {
  return im;
 }

 double abs()
 {
  return(Math.sqrt((this.Re()*this.Re())+(this.Im()*this.Im())));//square root of a^2+b^2
 }

 double arg()
 {
  return Math.atan2(im, re);
 }

 public String toString()
 {
  String str=("");
  if(this.Im()>0)				//for formatting it tests to see if imaginary number is negative
  str=(this.Re()+" + "+this.Im()+"i");
  else str=(this.Re()+" - "+(this.Im()*-1)+"i");
  return str;
 }

 public boolean equals(Object obj)//turns the object into a complex. Evaluates to true unless either the real numbers or the imaginary numbers are incongruent
 {
  boolean eq=true;
  Complex c;
  if(obj instanceof Complex)
  {
   c=(Complex)obj;
  if(this.Re()!=c.Re()) eq=false;
  else if(this.Im()!=c.Im()) eq=false;
  }
  return eq;
 }

 static Complex valueOf(double a, double b)
 {
  Complex c = new Complex(a, b);
  return c;
 }

 static Complex valueOf(double a)
 {
  Complex c = new Complex(a);
  return c;
 }

 static Complex valueOf(String s)
 {
  Complex c = new Complex(s);
  return c;
 }

 static double[] parseComplex(String str)//writes a string expression as a complex number
 {
  double[] part = new double[2];
  String s = str.trim();
  String NUM = "(\\d+\\.\\d*|\\.?\\d+)";
  String SGN = "[+-]?";
  String OP = "\\s*[+-]\\s*";
  String I = "i";
  String OR = "|";
  String REAL = SGN+NUM;
  String IMAG = SGN+NUM+"?"+I;
  String COMP = REAL+OR+IMAG+OR+REAL+OP+NUM+"?"+I;
  if(!s.matches(COMP))
  {
   throw new NumberFormatException("Cannot parse input string \" "+s+"\" as Complex");
  }
  s=s.replaceAll("\\s","");
  if(s.matches(REAL))
  {
   part[0]=Double.parseDouble(s);
   part[1]=0;
  }
  else if(s.matches(SGN+I))
  {
   part[0]=0;
   part[1]=Double.parseDouble(s.replace(I,"1.0"));
  }
  else if(s.matches(IMAG))
  {
   part[0]=0;
   part[1]=Double.parseDouble(s.replace(I, ""));
  }
  else if(s.matches(REAL+OP+I))
  {
   part[0]=Double.parseDouble(s.replaceAll("("+REAL+")"+OP+".+", "$1"));
   part[1]=Double.parseDouble(s.replaceAll(".+("+OP+")"+I, "$1"+"1.0"));
  }
  else 
  {
   part[0]=Double.parseDouble(s.replaceAll("("+REAL+").+" , "$1"));
   part[1]=Double.parseDouble(s.replaceAll(".+("+OP+NUM+")"+I, "$1"));
  }
  return part;
 }

}
