using System.IO.Ports;
using NineDigit.SerialTransport;
using Parity = System.IO.Ports.Parity;


class BloodPressureMonitor
{
    private SerialPort _serialPort;

    public BloodPressureMonitor(string portName)
    {
        _serialPort = new SerialPort(portName)
        {
            BaudRate = 115200,
            DataBits = 8,
            StopBits = (StopBits)StopBit.One,
            Parity = Parity.None,
            Handshake = Handshake.None
        };
    }

    public void OpenPort()
    {
        if (!_serialPort.IsOpen)
        {
            _serialPort.Open();
        }
    }

    public void ClosePort()
    {
        if (_serialPort.IsOpen)
        {
            _serialPort.Close();
        }
    }

    public string ReadData()
    {
        if (_serialPort.IsOpen)
        {
            try
            {
                byte[] buffer = new byte[_serialPort.BytesToRead];
                int bytesRead = _serialPort.Read(buffer, 0, buffer.Length);
                return BitConverter.ToString(buffer, 0, bytesRead);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error reading from port: " + ex.Message);
                return null;
            }
        }
        else
        {
            Console.WriteLine("Port is not open.");
            return null;
        }
    }

    public void ParseData(byte[] data)
    {
        // Implement data parsing logic based on the protocol
        // This is a simple example to get you started
        if (data.Length > 0)
        {
            // Check for the preamble
            if (data[0] == 0xAA && data[1] == 0x80)
            {
                // Extract and parse data
                int deviceVersion = data[2];
                int dataLength = data[3];
                int typeIdentifier = data[4];
                int typeSubCode = data[5];
                // Further parsing based on the protocol
                Console.WriteLine("Device Version: " + deviceVersion);
                Console.WriteLine("Data Length: " + dataLength);
                Console.WriteLine("Type Identifier: " + typeIdentifier);
                Console.WriteLine("Type Sub Code: " + typeSubCode);
            }
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        BloodPressureMonitor monitor = new BloodPressureMonitor("COM3");
        monitor.OpenPort();

        while (true)
        {
            string data = monitor.ReadData();
            if (data != null)
            {
                Console.WriteLine("Received data: " + data);
                byte[] dataBytes = ConvertHexStringToByteArray(data);
                monitor.ParseData(dataBytes);
            }
        }
    }

    static byte[] ConvertHexStringToByteArray(string hexString)
    {
        int numberChars = hexString.Length;
        byte[] bytes = new byte[numberChars / 2];
        for (int i = 0; i < numberChars; i += 2)
            bytes[i / 2] = Convert.ToByte(hexString.Substring(i, 2), 16);
        return bytes;
    }
}