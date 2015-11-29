import Sailfish.Silica 1.0

Page
{
	function navigate(page)
	{
		if (page !== undefined)
		{
			pageStack.popAttached();
			pageStack.replaceAbove(null, page)
			pageStack.pushAttached(playlistPage)
		}
	}
}
