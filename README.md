# Simulator for the Schrödinger equation


<p align="center">
  <img alt="Spine Toolbox" src="wavefunction.png" width="50%">
</p>

### Physics
The simulator solves the time-evolution of the given initial wavefunction according to the Schrödinger equation:

<p align="center">
  <img src="https://latex.codecogs.com/svg.image?i\hbar\frac{\partial}{\partial&space;t}\Psi(x,t)=-\frac{\hbar^2}{2m}\frac{\partial^2}{\partial&space;x^2}\Psi(x,t)&plus;V(x)\Psi(x,t)." alt="Schrödinger equation">
</p>

This solver currently only supports Gaussian wavepackets as initial states:
<p align="center">
  <img src="https://latex.codecogs.com/svg.image?\Psi(x,t)=\left(\frac{a}{a&plus;i\hbar&space;t/m}\right)^{3/2}\exp\left(-\frac{x^2}{2(a&plus;i\hbar&space;t/m)}\right)," alt="Gaussian wavepacket">
</p>
where a is a complex valued constant and m is the mass of the particle. With $t=0$, this reduces to the initial state used in the simulations:
<p align="center">
  <img src="https://latex.codecogs.com/svg.image?\Psi(x,0)=\exp\left(-\frac{x^2}{2a}\right)." alt="Initial state">
</p>

### Solver

The Schrödinger equation can be written in the form:
<p align="center">
  <img src="https://latex.codecogs.com/svg.image?\bg{FFBF00}\begin{align}\frac{\partial}{\partial&space;t}\Psi(x,t)&=\frac{i\hbar}{2m}\frac{\partial^2}{\partial&space;x^2}\Psi(x,t)-\frac{i}{\hbar}V(x)\Psi(x,t)\\&=F(\Psi,\partial_x^2\Psi,x,t)\end{align}" alt="Schrödinger equation 2">
</p>

Crank-Nicolson is used to compute the time-evolution of the wavefunction:
<p align="center">
  <img src="https://latex.codecogs.com/svg.image?\frac{\Psi_i^{n&plus;1}-\Psi_i^{n}}{\Delta&space;t}=\frac{1}{2}\left(F_i^{n&plus;1}&plus;F_i^{n}\right)," alt="Crank-Nicolson">
</p>
where the shorthand notation $\Psi_i^n=\Psi(i\Delta x, n\Delta t)$ is used, the notation $F_i^n$ follows the same logic.

The value of the laplacian $\partial_x^2\Psi_i^n$ can be approximated. The approximation is made by summing the Taylor series
for $\Psi_{i-1}^n$ and $\Psi_{i+1}^n$ around $x$, and discarding terms $\mathcal{O}(\Delta x^4)$. This leads to the approximation
<p align="center">
  <img src="https://latex.codecogs.com/svg.image?\partial_x^2\Psi_i^n\approx\frac{\Psi_{i-1}^n-2\Psi_i^n&plus;\Psi_{i&plus;1}^n}{\Delta&space;x^2}." alt="Second derivative respect to position">
</p>

## Usage

To show the animation of the systems time-evolution:
```
./bin/run_animation
```
