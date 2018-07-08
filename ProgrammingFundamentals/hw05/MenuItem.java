public class MenuItem {
	private String mTitle;
	private MenuCommand mCommand;
	
	public MenuItem(String mTitle, MenuCommand mCommand){
		this.mTitle = mTitle;
		this.mCommand = mCommand;
	}
	
	public String getTitle(){return mTitle;}
	
	public void execute(){
		if(mCommand != null)
			mCommand.run();
	}
	
}