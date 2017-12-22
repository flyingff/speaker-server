package net.flyingff.speaker;

import java.io.File;
import java.nio.charset.Charset;
import java.util.Base64;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.DataLine;

import fi.iki.elonen.NanoHTTPD;

public class TestSpeaker {
	public static void main(String[] args) throws Exception {
		// System.out.println(Base64.getEncoder().encodeToString("d:\\out.wav".getBytes(Charset.forName("utf-16LE"))));
		
		File f = speakToFile("中文测试");
		
		AudioInputStream ais = AudioSystem.getAudioInputStream(f);
		Clip clip = (Clip) AudioSystem
                   .getLine(new DataLine.Info(Clip.class, ais.getFormat()));
        clip.open(ais);
        clip.start();
        
        NanoHTTPD httpd = new NanoHTTPD(80) {
        	@Override
        	public Response serve(IHTTPSession arg0) {
        		return super.serve(arg0);
        	}
		};
		
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
	private static final File speakToFile(String str) {
		try {
			File tmp = File.createTempFile("what", ".wav");
			String path = Base64.getEncoder().encodeToString(tmp.getAbsolutePath().getBytes(Charset.forName("utf-16LE")));
			String cmd = TestSpeaker.class.getResource("speaker_to_file.exe").getFile() +" " + path;
			Process p = Runtime.getRuntime().exec(cmd);
			
			String toSpeak = Base64.getEncoder().encodeToString(str.getBytes(Charset.forName("utf-16LE")));
			p.getOutputStream().write(toSpeak.getBytes("iso-8859-1"));
			p.getOutputStream().close();
			p.waitFor();
            return tmp;
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
}
