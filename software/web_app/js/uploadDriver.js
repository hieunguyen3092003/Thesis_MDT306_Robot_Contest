// Assuming the upload driver is defined as `customUploadDriver` in uploadDriver.js
/**
 * Custom Upload Driver
 *
 * @param {AppContext} app
 * @param {DeviceContext} device
 * @param {ArrayBuffer | string} code
 * @param {() => void} logHandler
 * @param {(percent: number) => void} progressHandle
 * @param {(err: any, result: any) => void} finishHandler
 */

async function customUploadDriver(app, device, code, logHandler, progressHandle, finishHandler, errHandler) {
    // Check if device is connected
    if (!(await device.isConnected())) {
        app.error('Device is not connected');
        errHandler('Device is not connected');
        return;
    }

    // Helper functions
    var __waitForStr = (device, str, timeout) => {
        return new Promise((resolve, reject) => {
            var check = () => {
                let text = device.readText();
                app.log('received:', text);
                if (text.indexOf(str) > -1) {
                    resolve();
                } else if ((timeout -= 10) < 0) {
                    reject("timeout");
                } else setTimeout(check, 10);
            };
            setTimeout(check, 10, device);
        });
    };

    var __delay = (timeout) => {
        return new Promise((resolve) => {
            var check = () => {
                if ((timeout -= 10) < 0) {
                    resolve();
                } else setTimeout(check, 10);
            };
            setTimeout(check, 10);
        });
    };

    var textEncoder = new TextEncoder();

    // Start upload process
    device.setTextDecoder('utf8');
    device.writeRaw([0x03, 0x03]);
    await __delay(100);

    device.writeRaw([0x01]);
    await __delay(100);
    await __waitForStr(device, "REPL", 1000);

    device.writeText(textEncoder.encode("f = open('main.py', 'w')\r\n"));
    device.writeRaw([0x04]);
    await __delay(100);

    progressHandle(5);

    // Split code into lines and upload
    var codeLines = code.split("\n");
    let codeString = "";

    for (var lineNo = 0; lineNo < codeLines.length; lineNo++) {
        // Remove line endings and escape special characters
        var escapedCode = codeLines[lineNo].replace(/[\\]/g, "\\\\").replace(/["]/g, '\\"');

        codeString += 'f.write("' + escapedCode + '\\n")\r\n';

        if (codeString.length > 100 || lineNo === codeLines.length - 1) {
            device.writeText(textEncoder.encode(codeString));
            device.writeRaw([0x04]);
            await __delay(50);
            codeString = "";
            var percent = (lineNo / codeLines.length) * 100;
            progressHandle(percent);
        }
    }

    // Save file and execute
    device.writeText(textEncoder.encode("f.close()\r\n"));
    device.writeRaw([0x04]);
    await __delay(50);

    // Exit raw REPL mode and reset
    device.writeRaw([0x02]);
    await __delay(50);
    await __waitForStr(device, '>', 1000);

    device.writeRaw([0x04]); // Soft reset
    await __delay(100);

    finishHandler();
}


async function uploadCode() {
    const code = generatePythonCode(); // Get the Python code from Blockly
    const app = {}; // Define your app context or mock object if needed
    const device = {}; // Define your device context or actual device object
    const logHandler = (msg) => console.log(msg); // Define log handler function
    const progressHandle = (percent) => console.log("Progress:", percent); // Define progress handler function
    const finishHandler = () => console.log("Upload complete!"); // Define finish handler function
    const errHandler = (err) => console.error("Error:", err); // Define error handler function

    // Call the custom upload function
    try {
        await customUploadDriver(app, device, code, logHandler, progressHandle, finishHandler, errHandler);
    } catch (error) {
        console.error("Upload failed:", error);
    }
}