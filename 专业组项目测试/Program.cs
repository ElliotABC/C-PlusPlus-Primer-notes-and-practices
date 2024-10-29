using System.Net.NetworkInformation;

PhysicalAddress macAddress = NetworkInterface.GetAllNetworkInterfaces()[0].GetPhysicalAddress();
Console.WriteLine(macAddress);