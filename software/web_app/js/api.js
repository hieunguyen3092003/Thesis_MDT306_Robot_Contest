// Initialize the Blockly workspace
const workspace = Blockly.inject('blocklyDiv', {
    toolbox: document.getElementById('toolbox')
});

// Function to generate code and display it
function generateCode() {
    // Choose the language you want to generate (e.g., JavaScript, Python)
    const code = Blockly.Python.workspaceToCode(workspace);

    // Display generated code in the <pre> element
    document.getElementById('codeOutput').innerText = code;

    return code;
}

// Add a listener for any change in the workspace
workspace.addChangeListener(() => {
    generateCode();  // Generate code whenever the workspace changes
});

// Toggle view between Blockly and Python editor
function toggleView() {
    const blocklyDiv = document.getElementById('blocklyDiv');
    const pythonEditor = document.getElementById('pythonEditor');
    const toggleButton = document.querySelector("button");

    if (blocklyDiv.classList.contains('visible')) {
        // Switch to Python editor
        pythonEditor.value = generatePythonCode(); // Display generated Python code
        blocklyDiv.classList.remove('visible');
        pythonEditor.classList.add('visible');
        toggleButton.innerText = "Switch to Blockly";
    } else {
        // Switch back to Blockly
        blocklyDiv.classList.add('visible');
        pythonEditor.classList.remove('visible');
        toggleButton.innerText = "Switch to Python Editor";
    }
}