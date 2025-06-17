def divide(x, y):
    """Division of two numbers"""
    return x / y

def multiply(x, y):
    """Multiplication of two numbers"""
    return x * y

def calculate_power(voltage, current):
    """Power calculation (P = U*I)"""
    return multiply(voltage, current)

def calculate_energy(power, time):
    """Energy calculation (E = P*t)"""
    return multiply(power, time)

def calculate_current(power, voltage):
    """Current calculation (I = P/U)"""
    return divide(power, voltage)

def calculate_voltage(power, current):
    """Voltage calculation (U = P/I)"""
    return divide(power, current)

def main():
    print("Electricity Calculator")
    print("1. Power calculation (P = U*I)")
    print("2. Energy calculation (E = P*t)")
    print("3. Current calculation (I = P/U)")
    print("4. Voltage calculation (U = P/I)")
    print("0. Exit")
    
    while True:
        choice = input("\nSelect operation (0-4): ")
        
        if choice == "0":
            print("Exiting the program")
            break
            
        elif choice == "1":
            try:
                u = float(input("Enter voltage (V): "))
                i = float(input("Enter current (A): "))
                p = calculate_power(u, i)
                print(f"Power: {p:.2f} W")
            except ValueError:
                print("Error: enter numeric values")
                
        elif choice == "2":
            try:
                p = float(input("Enter power (W): "))
                t = float(input("Enter time (h): "))
                e = calculate_energy(p, t)
                print(f"Energy: {e:.2f} Wh")
            except ValueError:
                print("Error: enter numeric values")
                
        elif choice == "3":
            try:
                p = float(input("Enter power (W): "))
                u = float(input("Enter voltage (V): "))
                i = calculate_current(p, u)
                print(f"Current: {i:.2f} A")
            except ValueError:
                print("Error: enter numeric values")
                
        elif choice == "4":
            try:
                p = float(input("Enter power (W): "))
                i = float(input("Enter current (A): "))
                u = calculate_voltage(p, i)
                print(f"Voltage: {u:.2f} V")
            except ValueError:
                print("Error: enter numeric values")
                
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
