products = [
    {"name": "Laptop", "stock": 15},
    {"name": "Mouse", "stock": 8},
    {"name": "Keyboard", "stock": 12},
    {"name": "Monitor", "stock": 4},
    {"name": "USB Drive", "stock": 25},
    {"name": "Headphones", "stock": 9}
]

print("Products with stock less than 10:")
print("-" * 30)

# Display all products whose stock is less than 10
for product in products:
    if product["stock"] < 10:
        print(f"Product: {product['name']}, Stock: {product['stock']}")