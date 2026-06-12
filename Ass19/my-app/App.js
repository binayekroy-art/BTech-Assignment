import React, { useState } from 'react';
import { SafeAreaView, View, Text, TouchableOpacity, StyleSheet } from 'react-native';

const App = () => {
  const [count, setCount] = useState(0);
  const [isDark, setIsDark] = useState(false);

  const handleIncrement = () => setCount(prev => prev + 1);
  const handleDecrement = () => setCount(prev => (prev > 0 ? prev - 1 : 0));
  const handleReset = () => setCount(0);
  const toggleTheme = () => setIsDark(prev => !prev);

  const themeStyles = isDark ? darkStyles : lightStyles;

  return (
    <SafeAreaView style={[styles.container, themeStyles.container]}>
      <Text style={[styles.title, themeStyles.text]}>Simple Counter</Text>
      <Text style={[styles.counter, themeStyles.text]}>{count}</Text>
      <View style={styles.buttonRow}>
        <TouchableOpacity style={styles.button} onPress={handleIncrement}>
          <Text style={styles.buttonText}>Increment</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={handleDecrement}>
          <Text style={styles.buttonText}>Decrement</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={handleReset}>
          <Text style={styles.buttonText}>Reset</Text>
        </TouchableOpacity>
      </View>
      <TouchableOpacity style={styles.toggleButton} onPress={toggleTheme}>
        <Text style={styles.buttonText}>Toggle Theme</Text>
      </TouchableOpacity>
    </SafeAreaView>
  );
};

const base = {
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    padding: 20,
  },
  text: {
    fontSize: 24,
    marginBottom: 20,
  },
};

const lightStyles = StyleSheet.create({
  container: { ...base.container, backgroundColor: '#ffffff' },
  text: { ...base.text, color: '#000000' },
});

const darkStyles = StyleSheet.create({
  container: { ...base.container, backgroundColor: '#222222' },
  text: { ...base.text, color: '#ffffff' },
});

const styles = StyleSheet.create({
  title: { fontSize: 28, fontWeight: 'bold', marginBottom: 10 },
  counter: { fontSize: 48, fontWeight: '600', marginBottom: 20 },
  buttonRow: { flexDirection: 'row', marginBottom: 20 },
  button: { backgroundColor: '#4CAF50', padding: 10, marginHorizontal: 5, borderRadius:5 },
  toggleButton: { backgroundColor: '#2196F3', padding: 10, borderRadius:5 },
  buttonText: { color: '#fff', fontSize: 16 },
});

export default App;
