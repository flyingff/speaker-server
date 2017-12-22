package net.flyingff.speaker;

import java.nio.charset.Charset;
import java.util.Base64;
import java.util.Scanner;

public class TestSpeaker {
	public static void main(String[] args) throws Exception {
		System.out.println(Base64.getEncoder().encodeToString("d:\\out.wav".getBytes(Charset.forName("utf-16LE"))));
		
		/*try (Scanner sc = new Scanner(TestSpeaker.class.getResourceAsStream("test.txt"))){
			while(sc.hasNextLine()) {
				speak(sc.nextLine());
			}
		}
		*/
	}
	
	private static final void speak(String str) {
		try {
			String spk = Base64.getEncoder().encodeToString(str.getBytes(Charset.forName("utf-16LE")));
			String cmd = TestSpeaker.class.getResource("Speaker.exe").getFile() +" " + spk;
			Process p = Runtime.getRuntime().exec(cmd);
			p.waitFor();
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
	private static final void speakToFile(String str) {
		
	}
}
