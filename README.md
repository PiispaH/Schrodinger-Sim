# Simulator for the Schrödinger equation

### Physics
The simulator solves the time-evolution of the given initial wavefunction according to the Schrödinger equation:
$$
i\hbar\frac{\partial}{\partial t}\Psi(x, t)=-\frac{\hbar^2}{2m}\frac{\partial^2}{\partial x^2}\Psi(x, t)+V(x)\Psi(x, t).
$$
This solver currently only supports Gaussian wavepackets as initial states:
$$
\Psi(x, t)=\left(\frac{a}{a+i\hbar t/m}\right)^{3/2}\exp\left(-\frac{x^2}{2(a+i\hbar t/m)}\right),
$$
where a is a complex valued constant and m is the mass of the particle. With $t=0$, this reduces to the initial state used in the simulations:
$$
\Psi(x, 0)=\exp\left(-\frac{x^2}{2a}\right).
$$

### Solver

The Schrödinger equation can be written in the form:
$$\begin{align}
\frac{\partial}{\partial t}\Psi(x, t)&=\frac{i\hbar}{2m}\frac{\partial^2}{\partial x^2}\Psi(x, t)-\frac{i}{\hbar}V(x)\Psi(x, t) \\
&=F(\Psi, \partial_x^2\Psi, x, t).
\end{align}$$

Crank-Nicolson is used to compute the time-evolution of the wavefunction:
$$
\frac{\Psi_i^{n+1}-\Psi_i^{n}}{\Delta t}=\frac{1}{2}\left(F_i^{n+1}+F_i^{n}\right),
$$
where the shorthand notation $\Psi_i^n=\Psi(i\Delta x, n\Delta t)$ is used, and the.

## Usage

To show the animation of the systems time-evolution:
```
./bin/run_animation
```
