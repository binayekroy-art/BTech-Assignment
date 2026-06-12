# Simple Digital Counter & Theme Toggle App

## Overview
Build a single‑screen mobile application using **React Native**. The app functions as a digital counter that allows users to increment, decrement, and reset a number displayed on the screen. To make the app more interactive, it includes a **Theme Toggle** button that switches the screen's background and text colors between a Light Mode and a Dark Mode.

## Implementation Rules

### Core Layout
- Use standard React Native components: `View`, `Text`, and `TouchableOpacity` (or `Button`).
- The counter UI should be perfectly centered on the screen.

### State Management
- Use the `useState` hook to manage two pieces of state:
  1. `count` – the current counter value (integer).
  2. `isDarkMode` – the active theme mode (boolean).

### Counter Logic
- **Start at 0**.
- **Increment** button increases the count by 1.
- **Decrement** button decreases the count by 1 but never lets the counter go below 0.
- **Reset** button sets the count back to 0.

### Dynamic Styling
- **Light Mode (Default):** White background with dark text.
- **Dark Mode:** Dark gray/black background with white text.
- Clicking the **Toggle Theme** button instantly swaps these styles across the entire screen.

## Required Features
1. **UI Layout & Component Structure** – parent container, text display for the counter, and a clean arrangement of buttons using Flexbox (e.g., increment/decrement side‑by‑side). Use proper style properties (`flex`, `justifyContent`, `alignItems`, `fontSize`, `padding`).
2. **Counter State & Validation Logic** – implement `useState` for the counter, ensure decrement does nothing when count is 0.
3. **Dynamic Theme Toggling** – track theme state (`isDarkMode`). Apply conditional styling or ternary operators to switch `backgroundColor` and `color` based on the theme.
4. **Code Cleanliness & Best Practices** – readable code, meaningful function names (`handleIncrement`, `handleDecrement`, `handleReset`, `toggleTheme`), and no obvious runtime crashes.

## Example React Native Code (App.js)
```javascript
import React, { useState } from 'react';
import { StyleSheet, Text, View, TouchableOpacity } from 'react-native';

export default function App() {
  const [count, setCount] = useState(0);
  const [isDarkMode, setIsDarkMode] = useState(false);

  const handleIncrement = () => setCount(prev => prev + 1);
  const handleDecrement = () => setCount(prev => (prev > 0 ? prev - 1 : 0));
  const handleReset = () => setCount(0);
  const toggleTheme = () => setIsDarkMode(prev => !prev);

  const themeStyles = {
    backgroundColor: isDarkMode ? '#222' : '#fff',
    color: isDarkMode ? '#fff' : '#000',
  };

  return (
    <View style={[styles.container, { backgroundColor: themeStyles.backgroundColor }]}>
      <Text style={[styles.counter, { color: themeStyles.color }]}>{count}</Text>
      <View style={styles.buttonRow}>
        <TouchableOpacity style={styles.button} onPress={handleDecrement}>
          <Text style={styles.buttonText}>-</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={handleIncrement}>
          <Text style={styles.buttonText}>+</Text>
        </TouchableOpacity>
      </View>
      <TouchableOpacity style={styles.resetButton} onPress={handleReset}>
        <Text style={styles.buttonText}>Reset</Text>
      </TouchableOpacity>
      <TouchableOpacity style={styles.toggleButton} onPress={toggleTheme}>
        <Text style={styles.buttonText}>Toggle Theme</Text>
      </TouchableOpacity>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    padding: 20,
  },
  counter: {
    fontSize: 48,
    marginBottom: 30,
  },
  buttonRow: {
    flexDirection: 'row',
    marginBottom: 20,
  },
  button: {
    backgroundColor: '#007bff',
    padding: 15,
    marginHorizontal: 10,
    borderRadius: 8,
  },
  resetButton: {
    backgroundColor: '#6c757d',
    padding: 12,
    borderRadius: 8,
    marginBottom: 15,
  },
  toggleButton: {
    backgroundColor: '#28a745',
    padding: 12,
    borderRadius: 8,
  },
  buttonText: {
    color: '#fff',
    fontSize: 18,
  },
});
```

## How to Run
1. **Prerequisites** – Install Node.js, Yarn/npm, and the React Native CLI.
2. Initialize a new project:
   ```bash
   npx react-native init Ass19CounterApp
   cd Ass19CounterApp
   ```
3. Replace the generated `App.js` with the example above (or customize).
4. Run on Android or iOS:
   ```bash
   npx react-native run-android   # Android device/emulator
   npx react-native run-ios       # iOS simulator
   ```

## Notes
- Android developers should run the app on a real device or Android emulator in development mode.
- iOS developers can test using the Android Studio emulator if they prefer.

---
*This README provides the specification and a starter code snippet for the Simple Digital Counter & Theme Toggle App.*
