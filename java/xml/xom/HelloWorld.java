import nu.xom.*;

public class HelloWorld {
	
	public static void main(String[] args) {
		Element root = new Element("root");
		root.appendChild("\n Hello World! \n");
		Document doc = new Document(root);
		String result = doc.toXML();
		System.out.println(result);
	}
}
